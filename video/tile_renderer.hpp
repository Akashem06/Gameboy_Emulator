#pragma once

#include "common.hpp"
#include "framebuffer.hpp"
#include "memory_controller.hpp"

class PPU;

class TileRenderer {
 private:
  PPU *ppu = nullptr;

  void render_background(u8 line);
  void render_window(u8 line);

 public:
  Register8 scy;  // 0xFF42 - Scroll Y
  Register8 scx;  // 0xFF43 - Scroll X
  Register8 wy;   // 0xFF4A - Window Y
  Register8 wx;   // 0xFF4B - Window X
  Register8 bgp;  // 0xFF47 - Background Palette

  TileRenderer();

  void render_scanline(u8 line);

  void set_ppu(PPU *ppu);
};
