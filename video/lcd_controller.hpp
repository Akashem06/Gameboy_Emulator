#pragma once

#include "common.hpp"
#include "mem.h"
#include "register.hpp"

class LCDController {
 private:
  Register8 lcd_control;
  Register8 lcd_status;

  void update_status();

 public:
  LCDController();

  u8 read(Address address);
  void write(Address address, u8 value);

  bool is_display_enabled();
  bool is_window_enabled();
  bool is_spirte_enabled();
};
