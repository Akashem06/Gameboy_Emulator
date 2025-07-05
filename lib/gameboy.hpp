#pragma once

#include "cartridge.hpp"
#include "common.hpp"
#include "config.hpp"
#include "cpu.hpp"
#include "input.hpp"
#include "memory_controller.hpp"
#include "ppu.hpp"
#include "serial.hpp"
#include "timer.hpp"

#define HIGH_RAM_START_ADDRESS 0xFFFEU
#define PROGRAM_COUNTER_START_VALUE 0x0100U

class Gameboy {
 public:
  Gameboy(Config *cfg);

  int run(int argc, char **argv);

  void reset();
  void pause();
  void abort();

  bool isPaused() const;
  bool isRunning() const;
  u64 getTicks() const;

  CPU &get_cpu() {
    return cpu;
  }

  PPU &get_ppu() {
    return ppu;
  }

  MemoryController &get_memory_controller() {
    return mem_ctrl;
  }

  Cartridge &get_cartridge() {
    return cartridge;
  }

  Timer &get_timer() {
    return timer;
  }

  Serial &get_serial() {
    return serial;
  }

  Input &get_input() {
    return input;
  }

  Config *get_config() {
    return config;
  }

 private:
  CPU cpu;
  PPU ppu;
  MemoryController mem_ctrl;
  Cartridge cartridge;
  Timer timer;
  Serial serial;
  Input input;

  Config *config = nullptr;

  bool paused;
  bool running;
  u64 ticks;
};
