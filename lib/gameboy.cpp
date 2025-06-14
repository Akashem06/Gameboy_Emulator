#include "gameboy.hpp"

#include <stdbool.h>

#include <cstdio>

#include "common.hpp"
#include "log.hpp"
#include "sdl_ui.hpp"

Gameboy::Gameboy() : cpu(&mem_ctrl), mem_ctrl(&cpu, &cartridge), cartridge() {
  paused = false;
  running = false;
  ticks = 0U;
}

int Gameboy::run(int argc, char **argv) {
  if (argv == nullptr) {
    return -1;
  }

  if (argc < 2) {
    log_error("ERROR: Did not receive ROM file name\n");
    return -2;
  }

  if (!cartridge.readInfo(argv[1])) {
    log_error("Failed to load ROM file: %s\n", argv[1]);
    return -3;
  }

  log_info("Cart loaded..\n");

  SDLUI ui = SDLUI();

  cpu.init();

  running = true;
  paused = false;
  ticks = 0;

  while (running) {
    if (paused) {
      delay_ms(10);
      continue;
    }

    if (!cpu.step()) {
      log_info("CPU Stopped\n");
      return -4;
    }

    ticks++;
  }

  return 0;
}

void Gameboy::reset() {
  paused = false;
  running = false;
  ticks = 0U;
}

bool Gameboy::isPaused() const {
  return paused;
}

bool Gameboy::isRunning() const {
  return running;
}

u64 Gameboy::getTicks() const {
  return ticks;
}

void Gameboy::pause() {
  paused = true;
}

void Gameboy::abort() {
  running = false;
}
