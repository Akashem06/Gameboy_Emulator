#pragma once

#include "common.hpp"
#include "mem.h"
#include "register.hpp"

class PPU;

class LCDController {
 private:
  PPU *ppu = nullptr;

 public:
  Register8 lcdc;  // 0xFF40 - LCD Control
  Register8 stat;  // 0xFF41 - LCD Status
  Register8 ly;    // 0xFF44 - LY (Current Scanline)
  Register8 lyc;   // 0xFF45 - LYC (LY Compare)

  LCDController();

  u8 read(Address address);
  void write(Address address, u8 value);

  bool is_display_enabled();
  bool is_window_enabled();
  bool is_sprite_enabled();
  void update_status();

  void set_ppu(PPU *ppu);
};
