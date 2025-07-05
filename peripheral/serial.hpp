#pragma once

#include "common.hpp"
#include "config.hpp"

class Gameboy;

class Serial {
 private:
  Gameboy *gameboy = nullptr;
  u8 sb_register;
  u8 sc_register;

 public:
  Serial();

  u8 read();
  u8 read_control();
  void write(u8 byte);
  void write_control(u8 byte);

  void set_gameboy(Gameboy *gb);
};
