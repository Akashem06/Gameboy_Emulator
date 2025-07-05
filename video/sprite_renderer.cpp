#include "sprite_renderer.hpp"

#include "gameboy.hpp"
#include "memory_controller.hpp"
#include "ppu.hpp"

SpriteRenderer::SpriteRenderer() {
  obp0.set(0xFFU);
  obp1.set(0xFFU);
}

void SpriteRenderer::render_scanline(u8 line) {
  auto &mem = ppu->get_gameboy()->get_memory_controller();
  auto &lcdc = ppu->get_lcd().lcdc;

  bool sprite_enable = lcdc.get() & 0x02;
  if (!sprite_enable) return;

  bool sprite_size_8x16 = lcdc.get() & 0x04;

  struct Sprite {
    u8 y, x, tile, attributes;
  };

  std::vector<Sprite> sprites_on_line;

  // Iterate through OAM (max 40 sprites)
  for (int i = 0; i < 40; i++) {
    u16 addr = 0xFE00 + i * 4;
    Sprite sprite = {
      .y = mem.read(addr),
      .x = mem.read(addr + 1),
      .tile = mem.read(addr + 2),
      .attributes = mem.read(addr + 3),
    };

    u8 sprite_height = sprite_size_8x16 ? 16 : 8;

    // Check if sprite overlaps this scanline
    if ((line + 16) >= sprite.y && (line + 16) < (sprite.y + sprite_height)) {
      sprites_on_line.push_back(sprite);
      if (sprites_on_line.size() >= 10) break;  // hardware limit: max 10 sprites per line
    }
  }

  for (auto &sprite : sprites_on_line) {
    int sprite_height = sprite_size_8x16 ? 16 : 8;
    int sprite_line = line + 16 - sprite.y;

    // Handle vertical flip
    if (sprite.attributes & (1 << 6)) {
      sprite_line = sprite_height - 1 - sprite_line;
    }

    u16 tile_addr = 0x8000 + sprite.tile * 16;
    if (sprite_size_8x16) {
      tile_addr = 0x8000 + ((sprite.tile & 0xFE) * 16);
    }

    u8 byte1 = mem.read(tile_addr + sprite_line * 2);
    u8 byte2 = mem.read(tile_addr + sprite_line * 2 + 1);

    for (int x_pixel = 0; x_pixel < 8; x_pixel++) {
      int x_screen = sprite.x - 8 + (sprite.attributes & (1 << 5) ? 7 - x_pixel : x_pixel);
      if (x_screen < 0 || x_screen >= Framebuffer::WIDTH) continue;

      u8 bit = 7 - x_pixel;
      u8 color_num = ((byte2 >> bit) & 0x1) << 1 | ((byte1 >> bit) & 0x1);

      if (color_num == 0) continue;  // color 0 is transparent for sprites

      // Apply palette
      u8 palette_reg = (sprite.attributes & (1 << 4)) ? obp1.get() : obp0.get();
      u8 color = (palette_reg >> (color_num * 2)) & 0x03;

      // Handle priority flag (OBJ-to-BG Priority bit)
      bool bg_priority = sprite.attributes & (1 << 7);
      if (bg_priority) {
        u8 bg_color = ppu->get_framebuffer().get_pixel(x_screen, line);
        if (bg_color != 0) continue;  // behind non-zero BG pixel
      }

      ppu->get_framebuffer().set_pixel(x_screen, line, color);
    }
  }
}

void SpriteRenderer::set_ppu(PPU *ppu) {
  this->ppu = ppu;
}
