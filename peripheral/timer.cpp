#include "timer.hpp"

#include "gameboy.hpp"
#include "log.hpp"

u64 Timer::clocks_needed_to_increment() {
  switch (get_timer_control()) {
    case 0:
      return CLOCK_RATE / 4096;
    case 1:
      return CLOCK_RATE / 262144;
    case 2:
      return CLOCK_RATE / 65536;
    case 3:
      return CLOCK_RATE / 16384;
    default:
      log_error("Invalid calculation in timer");
  }

  return 0;
}

Timer::Timer() {}

void Timer::tick(u64 cycles) {
  u8 new_divider = static_cast<u8>(divider.get() + cycles);
  divider.set(new_divider);

  clocks += cycles * CLOCKS_PER_CYCLE;

  auto timer_is_on = timer_control.check_bit(2);
  if (timer_is_on == 0) {
    return;
  }

  auto clock_limit = clocks_needed_to_increment();

  if (clocks >= clock_limit) {
    clocks = clocks % clock_limit;

    u8 old_timer_counter = timer_counter.get();
    timer_counter.increment();

    if (timer_counter.get() < old_timer_counter) {
      gameboy->get_cpu().interrupt_flag.set_bit_to(2, true);
      timer_counter.set(timer_modulo.get());
    }
  }

  log_debug("Timer counter: %u\r\n", timer_counter);
}

u8 Timer::get_divider() {
  return divider.get();
}

u8 Timer::get_timer_counter() {
  return timer_counter.get();
}

u8 Timer::get_timer_modulo() {
  return timer_modulo.get();
}

u8 Timer::get_timer_control() {
  return timer_control.get() & 0x3U;
}

void Timer::reset_divider() {
  divider.set(0U);
}

void Timer::set_timer_counter(u8 value) {
  timer_counter.set(value);
}

void Timer::set_timer_counter_modulo(u8 value) {
  timer_modulo.set(value);
}

void Timer::set_timer_counter_control(u8 value) {
  timer_control.set(value);
}

void Timer::set_gameboy(Gameboy *gb) {
  this->gameboy = gb;
}
