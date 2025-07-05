#pragma once

#include "common.hpp"
#include "framebuffer.hpp"
#include "memory_controller.hpp"

class PPU;

class SpriteRenderer {
 private:
  PPU *ppu = nullptr;

  void fetch_sprites(u8 line);
  void draw_sprites(u8 line);

 public:
  Register8 obp0;  // 0xFF48 - Object Palette 0
  Register8 obp1;  // 0xFF49 - Object Palette 1

  SpriteRenderer();

  void render_scanline(u8 line);

  void set_ppu(PPU *ppu);
};
