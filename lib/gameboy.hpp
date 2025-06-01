#pragma once

#include <stdbool.h>

#include "cartridge.hpp"
#include "common.hpp"
#include "cpu.hpp"
#include "memory_controller.hpp"

#define HIGH_RAM_START_ADDRESS 0xFFFEU
#define PROGRAM_COUNTER_START_VALUE 0x0100U

class Gameboy {
 private:
  bool paused;
  bool running;
  u64 ticks;

  CPU cpu;

  MemoryController mem_ctrl;

  Cartridge cartridge;

 public:
  Gameboy();

  int run(int argc, char **argv);

  void reset();

  bool isPaused() const;
  bool isRunning() const;
  u64 getTicks() const;

  void pause();
  void abort();
};
