#pragma once

#include "common.hpp"
#include "framebuffer.hpp"
#include "memory_controller.hpp"

class TileRenderer {
 public:
  TileRenderer(MemoryController *mem_ctrl, Framebuffer *framebuffer);

  void render_scanline(u8 line);

 private:
  MemoryController *mem_ctrl;
  Framebuffer *framebuffer;

  void render_background(u8 line);
  void render_window(u8 line);
};
