#pragma once

#include "common.hpp"
#include "framebuffer.hpp"
#include "memory_controller.hpp"

class SpriteRenderer {
 public:
  SpriteRenderer(MemoryController *mem_ctrl, Framebuffer *framebuffer);

  void render_scanline(u8 line);

 private:
  MemoryController *mem_ctrl;
  Framebuffer *framebuffer;

  void fetch_sprites(u8 line);
  void draw_sprites(u8 line);
};
