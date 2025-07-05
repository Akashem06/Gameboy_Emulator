#pragma once

#include "common.hpp"

class Gameboy;

enum class Button {
  Up,
  Down,
  Left,
  Right,
  A,
  B,
  Select,
  Start,
};

class Input {
 private:
  Gameboy *gameboy = nullptr;
  void set_button(Button button, bool set);

  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool a = false;
  bool b = false;
  bool select = false;
  bool start = false;

  bool button_switch = false;
  bool direction_switch = false;

 public:
  void button_pressed(Button button);
  void button_released(Button button);
  void write(u8 set);

  u8 get_input();
  void set_gameboy(Gameboy *gb);
};
