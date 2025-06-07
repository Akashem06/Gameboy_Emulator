#pragma once

#include <array>
#include <cstdint>

#include "common.hpp"

class Framebuffer {
 public:
  static constexpr u32 WIDTH = 160U;
  static constexpr u32 HEIGHT = 144U;

  Framebuffer();

  void set_pixel(u8 x, u8 y, u8 color);
  u8 get_pixel(u8 x, u8 y);
  void clear();

 private:
  std::array<std::array<u8, WIDTH>, HEIGHT> pixels;
};
