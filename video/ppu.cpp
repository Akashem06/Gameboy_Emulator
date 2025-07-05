#include "ppu.hpp"
#include "log.hpp"
#include "cpu.hpp"
#include "gameboy.hpp"

PPU::PPU() : lcd(), tile_renderer(), sprite_renderer(), framebuffer() {
  lcd.set_ppu(this);
  framebuffer.set_ppu(this);
  tile_renderer.set_ppu(this);
  sprite_renderer.set_ppu(this);

  current_mode = Mode::OAM_SEARCH;
}

void PPU::tick(int cycles) {
  int ppu_cycles = cycles * 4;
  for (int i = 0; i < ppu_cycles; i++) {
    step();
  }
}

void PPU::step() {
  if (!lcd.is_display_enabled()) {
    mode_clock = 0;
    lcd.ly.set(0);
    set_mode(Mode::HBLANK);
    log_warn("PPU is not enabled\r\n");
    return;
  }

  mode_clock++;
  switch (current_mode) {
    case Mode::OAM_SEARCH:
      if (mode_clock >= CLOCKS_PER_SCANLINE_OAM) {
        set_mode(Mode::PIXEL_TRANSFER);
      }
      break;
    case Mode::PIXEL_TRANSFER:
      if (mode_clock >= CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM) {
        set_mode(Mode::HBLANK);
        render_scanline();
      }
      break;
    
  case Mode::HBLANK:
  if (mode_clock >= CLOCKS_PER_SCANLINE) {
    mode_clock = 0;
    u8 new_ly = lcd.ly.get() + 1;
    lcd.ly.set(new_ly);
    lcd.update_status();

    if (new_ly == VBLANK_START_LINE) {  // 144
      set_mode(Mode::VBLANK);
      gameboy->get_cpu().request_interrupt(static_cast<u8>(interrupts::flags::vblank));
    } else {
      set_mode(Mode::OAM_SEARCH);
    }
  }
  break;

case Mode::VBLANK:
  if (mode_clock >= CLOCKS_PER_SCANLINE) {
    mode_clock = 0;
    u8 new_ly = lcd.ly.get() + 1;

    if (new_ly > VBLANK_END_LINE) {  // 153
      new_ly = 0;
      set_mode(Mode::OAM_SEARCH);
    }

    lcd.ly.set(new_ly);
  }
  break;

  }
}

void PPU::render_scanline() {
  tile_renderer.render_scanline(lcd.ly.get());
  sprite_renderer.render_scanline(lcd.ly.get());
}

void PPU::set_mode(Mode mode) {
  current_mode = mode;
  mode_clock = 0;
  u8 stat_val = lcd.stat.get() & 0xFCU;

  switch (mode) {
    case Mode::HBLANK:
      stat_val |= 0U;
      break;
    case Mode::VBLANK:
      stat_val |= 1U;
      break;
    case Mode::OAM_SEARCH:
      stat_val |= 2U;
      break;
    case Mode::PIXEL_TRANSFER:
      stat_val |= 3U;
      break;
  }

  lcd.stat.set(stat_val);
}

void PPU::set_gameboy(Gameboy *gb) {
    this->gameboy = gb;
}
