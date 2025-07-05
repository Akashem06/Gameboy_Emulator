#pragma once

#include "common.hpp"
#include "register.hpp"

#define CLOCKS_PER_CYCLE 4

class Gameboy;

class Timer {
 private:
  Gameboy *gameboy = nullptr;
  u64 clocks_needed_to_increment();
  u64 clocks = 0;

  Register8 divider;
  Register8 timer_counter;

  Register8 timer_modulo;
  Register8 timer_control;

 public:
  Timer();

  void tick(u64 cycles);

  u8 get_divider();
  u8 get_timer_counter();
  u8 get_timer_modulo();
  u8 get_timer_control();

  void reset_divider();
  void set_timer_counter(u8 value);
  void set_timer_counter_modulo(u8 value);
  void set_timer_counter_control(u8 value);

  void set_gameboy(Gameboy *gb);
};