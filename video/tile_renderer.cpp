
#include "tile_renderer.hpp"

#include "gameboy.hpp"
#include "memory_controller.hpp"
#include "ppu.hpp"

TileRenderer::TileRenderer() {
  bgp.set(0xFCU);
}

void TileRenderer::render_scanline(u8 line) {
  render_background(line);
}

void TileRenderer::render_background(u8 line) {
  auto &mem = ppu->get_gameboy()->get_memory_controller();
  auto &lcdc = ppu->get_lcd().lcdc;

  bool bg_enable = lcdc.get() & 0x01;
  if (!bg_enable) {
    // Background disabled -> white screen
    for (u8 x = 0; x < Framebuffer::WIDTH; ++x) {
      ppu->get_framebuffer().set_pixel(x, line, 0);
    }
    return;
  }

  u16 bg_tile_map_addr = (lcdc.get() & 0x08) ? 0x9C00 : 0x9800;
  bool signed_tile_indices = !(lcdc.get() & 0x10);
  u16 tile_data_addr = signed_tile_indices ? 0x8800 : 0x8000;

  u8 scy_val = scy.get();
  u8 scx_val = scx.get();

  u8 y_in_bg = (line + scy_val) & 0xFF;

  for (u8 x = 0; x < Framebuffer::WIDTH; ++x) {
    u8 x_in_bg = (x + scx_val) & 0xFF;

    u16 tile_x = x_in_bg / 8;
    u16 tile_y = y_in_bg / 8;
    u16 tile_map_index = tile_y * 32 + tile_x;

    u16 tile_entry_addr = bg_tile_map_addr + tile_map_index;
    i8 tile_number = static_cast<i8>(mem.read(tile_entry_addr));

    u16 tile_addr = 0;
    if (signed_tile_indices) {
      tile_addr = tile_data_addr + ((tile_number + 128) * 16);
    } else {
      tile_addr = tile_data_addr + (tile_number * 16);
    }

    u8 line_in_tile = y_in_bg % 8;
    u8 byte1 = mem.read(tile_addr + line_in_tile * 2);
    u8 byte2 = mem.read(tile_addr + line_in_tile * 2 + 1);

    u8 bit = 7 - (x_in_bg % 8);
    u8 color_num = ((byte2 >> bit) & 0x1) << 1 | ((byte1 >> bit) & 0x1);

    // Apply palette from BGP register
    u8 palette = bgp.get();
    u8 color = (palette >> (color_num * 2)) & 0x03;

    ppu->get_framebuffer().set_pixel(x, line, color);
  }
}

void TileRenderer::set_ppu(PPU *ppu) {
  this->ppu = ppu;
}