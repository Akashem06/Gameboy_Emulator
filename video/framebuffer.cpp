#include "framebuffer.hpp"

Framebuffer::Framebuffer() {
  clear();
}

void Framebuffer::set_pixel(u8 x, u8 y, u8 color) {
  if (x < WIDTH && y < HEIGHT) {
    pixels[y][x] = color;
  }
}

u8 Framebuffer::get_pixel(u8 x, u8 y) {
  if (x < WIDTH && y < HEIGHT) {
    return pixels[y][x];
  }
  return 0U;
}

void Framebuffer::clear() {
  for (auto &row : pixels) {
    row.fill(0U);
  }
}

void Framebuffer::set_ppu(PPU *ppu) {
  this->ppu = ppu;
}
