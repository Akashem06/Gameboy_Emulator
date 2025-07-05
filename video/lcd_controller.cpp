#include "lcd_controller.hpp"

#include "gameboy.hpp"
#include "interrupts.hpp"
#include "ppu.hpp"

LCDController::LCDController() {
  lcdc.set(0x91U);
  stat.set(0x85U);
}

u8 LCDController::read(Address address) {
  switch (address) {
    case 0xFF40U:
      return lcdc.get();
    case 0xFF41U:
      return stat.get();
    case 0xFF44U:
      return ly.get();
    case 0xFF45U:
      return lyc.get();
    default:
      return 0xFFU;
  }
}

void LCDController::write(Address address, u8 value) {
  switch (address) {
    case 0xFF40U:
      lcdc.set(value);
      break;
    case 0xFF41U:
      stat.set(value & 0x78);
      break;  // Only writable bits
    case 0xFF44U:
      break;  // Read-only LY
    case 0xFF45U:
      lyc.set(value);
      break;
  }
}

void LCDController::update_status() {
  // Set LY=LYC coincidence
  if (ly.get() == lyc.get()) {
    stat.set(stat.get() | 0x04);  // Set coincidence flag
    if (stat.get() & 0x40) {
      // If LY=LYC interrupt enabled
      ppu->get_gameboy()->get_cpu().request_interrupt(static_cast<u8>(interrupts::flags::lcdc_status));
    }
  } else {
    stat.set(stat.get() & ~0x04);
  }
}

bool LCDController::is_display_enabled() {
  return lcdc.get() & 0x80U;
}

bool LCDController::is_window_enabled() {
  return lcdc.get() & 0x20U;
}

bool LCDController::is_sprite_enabled() {
  return lcdc.get() & 0x02U;
}

void LCDController::set_ppu(PPU *ppu) {
  this->ppu = ppu;
}
