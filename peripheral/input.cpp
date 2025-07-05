#include "input.hpp"

#include "gameboy.hpp"

void Input::set_button(Button button, bool set) {
  if (button == Button::Up) {
    up = set;
  }
  if (button == Button::Down) {
    down = set;
  }
  if (button == Button::Left) {
    left = set;
  }
  if (button == Button::Right) {
    right = set;
  }
  if (button == Button::A) {
    a = set;
  }
  if (button == Button::B) {
    b = set;
  }
  if (button == Button::Select) {
    select = set;
  }
  if (button == Button::Start) {
    start = set;
  }
}

void Input::button_pressed(Button button) {
  set_button(button, true);
}

void Input::button_released(Button button) {
  set_button(button, false);
}

void Input::write(u8 set) {
  direction_switch = (set & (1U << 4U)) == 0;
  button_switch = (set & (1U << 5U)) == 0;
}

u8 Input::get_input() {
  u8 buttons = 0xFU;

  if (direction_switch) {
    buttons |= ((!right) << 0U);
    buttons |= ((!left) << 1U);
    buttons |= ((!up) << 2U);
    buttons |= ((!down) << 3U);
  }

  if (button_switch) {
    buttons |= ((!a) << 0U);
    buttons |= ((!b) << 1U);
    buttons |= ((!select) << 2U);
    buttons |= ((!start) << 3U);
  }

  buttons |= ((!direction_switch) << 4U);
  buttons |= ((!button_switch) << 5U);

  return buttons;
}

void Input::set_gameboy(Gameboy *gb) {
  this->gameboy = gb;
}
