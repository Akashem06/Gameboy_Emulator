#include "gameboy.hpp"

#include <stdbool.h>

#include <cstdio>

#include "common.hpp"
#include "log.hpp"
#include "sdl_ui.hpp"
#include "sdl_ui_debugger.hpp"

Gameboy::Gameboy(Config *cfg) : cpu(), ppu(), mem_ctrl(), cartridge(), timer(), serial(), input() {
  cpu.set_gameboy(this);
  ppu.set_gameboy(this);
  mem_ctrl.set_gameboy(this);
  cartridge.set_gameboy(this);
  timer.set_gameboy(this);
  serial.set_gameboy(this);
  input.set_gameboy(this);

  cpu.get_opcode_handler().set_gameboy(this);

  config = cfg;
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
  SDLUI_Debugger debugger_disiplay = SDLUI_Debugger();

  cpu.init();

  running = true;
  paused = false;
  ticks = 0;

  const int cycles_per_frame = 70224;  // Each frame has 70224 machine cycles
  int accumulated_cycles = 0;

  while (running) {
    ui.handleEvents();

    if (ui.abortEvent()) {
      break;
    }

    int cycles = cpu.step();
  
    timer.tick(cycles);
    ppu.tick(cycles);

    ticks += cycles;
    accumulated_cycles += cycles;
  
    if (accumulated_cycles >= cycles_per_frame) {
      // One frame complete -> render
      ui.renderFrame(ppu.get_framebuffer());
      debugger_disiplay.set_developer_name("Aryan Kashem's Gameboy");
      debugger_disiplay.set_ly(ppu.get_lcd_ly().get());
      debugger_disiplay.set_instruction_cycles(accumulated_cycles);
      debugger_disiplay.set_status_text("Running");
      debugger_disiplay.set_registers(cpu.af.get(), cpu.bc.get(), cpu.de.get(), cpu.hl.get(), cpu.sp.get(), cpu.pc.get());
      debugger_disiplay.render();
      accumulated_cycles -= cycles_per_frame;
    }
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
