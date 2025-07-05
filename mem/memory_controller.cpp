#include "memory_controller.hpp"

#include "boot_rom.h"
#include "gameboy.hpp"
#include "log.hpp"

MemoryController::MemoryController() {
  work_ram = std::vector<u8>(0x2000U);
  oam_ram = std::vector<u8>(0x00A0U);
  high_ram = std::vector<u8>(0x80U);
  vram = std::vector<u8>(0x2000U);
}

u8 MemoryController::read(const Address address) {
  u8 value = 0U;

  /* Cartridge ROM memory */
  if (MEMORY_IN_RANGE(address, 0x0000U, 0x7FFFU)) {
    if (MEMORY_IN_RANGE(address, 0x0000U, 0x00FFU) && boot_rom_active()) {
      // log_trace("Reading from bootrom address: %u\r\n", address);
      return boot_rom[address];
    }

    value = gameboy->get_cartridge().readROM(address);
  }
  /* VRAM */
  else if (MEMORY_IN_RANGE(address, 0x8000U, 0x9FFFU)) {
    value = vram.at(address - 0x8000U);
  }

  /* Cartridge RAM */
  else if (MEMORY_IN_RANGE(address, 0xA000U, 0xBFFFU)) {
    value = gameboy->get_cartridge().readRAM(address);
  }

  /* WRAM Bank  */
  else if (MEMORY_IN_RANGE(address, 0xC000U, 0xDFFFU)) {
    value = work_ram.at(address - 0xC000U);
  }

  /* Echo RAM */
  else if (MEMORY_IN_RANGE(address, 0xE000U, 0xFDFFU)) {
    value = work_ram.at(address - 0xE000U);
  }

  /* OAM */
  else if (MEMORY_IN_RANGE(address, 0xFE00U, 0xFE9FU)) {
    value = oam_ram.at(address - 0xFE00U);
  }

  /* Reserved */
  else if (MEMORY_IN_RANGE(address, 0xFEA0U, 0xFEFFU)) {
  }

  /* I/O Registers */
  else if (MEMORY_IN_RANGE(address, 0xFF00U, 0xFF7FU)) {
    value = read_io(address);
  }

  /* High RAM */
  else if (MEMORY_IN_RANGE(address, 0xFF80U, 0xFFFEU)) {
    value = high_ram.at(address - 0xFF80U);
  }

  /* Interrupt Enable Register */
  else if (address == 0xFFFFU) {
    value = gameboy->get_cpu().interrupt_enabled_reg.get();
  }

  /* Invalid address */
  else {
  }

  return value;
}

u8 MemoryController::read_io(const Address address) {
  u8 value = 0x00U;

  switch (address) {
    case 0xFF00U:
      value = gameboy->get_input().get_input();
      log_debug("Polling input/joystick %u\r\n", value);
      break;

    case 0xFF01U:
      value = gameboy->get_serial().read();
      log_debug("Polling serial data %u\r\n", value);
      break;

    case 0xFF02U:
      value = gameboy->get_serial().read_control();
      log_debug("Polling serial control %u\r\n", value);
      break;

    case 0xFF03U:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    case 0xFF04U:
      value = gameboy->get_timer().get_divider();
      log_debug("Polling timer divider %u\r\n", value);
      break;

    case 0xFF05U:
      value = gameboy->get_timer().get_timer_counter();
      log_debug("Polling timer counter %u\r\n", value);
      break;

    case 0xFF06U:
      value = gameboy->get_timer().get_timer_modulo();
      log_debug("Polling timer modulo %u\r\n", value);
      break;

    case 0xFF07U:
      value = gameboy->get_timer().get_timer_control();
      log_debug("Polling timer control %u\r\n", value);
      break;

    case 0xFF08U:
    case 0xFF09U:
    case 0xFF0AU:
    case 0xFF0BU:
    case 0xFF0CU:
    case 0xFF0DU:
    case 0xFF0EU:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    case 0xFF0FU:
      value = gameboy->get_cpu().interrupt_flag.get();
      break;

    /* TODO: Audio - Channel 1: Tone & Sweep */
    case 0xFF10U:
    case 0xFF11U:
    case 0xFF12U:
    case 0xFF13U:
    case 0xFF14U:
      value = 0xFFU;
      break;

    case 0xFF15U:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    /* TODO: Audio - Channel 2: Tone */
    case 0xFF16U:
    case 0xFF17U:
    case 0xFF18U:
    case 0xFF19U:
      value = 0xFFU;
      break;

    /* TODO: Audio - Channel 3: Wave Output */
    case 0xFF1AU:
    case 0xFF1BU:
    case 0xFF1CU:
    case 0xFF1DU:
    case 0xFF1EU:
    case 0xFF1FU:
      value = 0xFF;
      break;

    /* TODO: Audio - Channel 4: Noise */
    case 0xFF20U:
    case 0xFF21U:
    case 0xFF22U:
    case 0xFF23U:
      value = 0xFFU;
      break;

    /* TODO: Audio - Channel control/ON-OFF/Volume */
    case 0xFF24U:
      value = 0xFFU;
      break;

    /* TODO: Audio - Selection of sound output terminal */
    case 0xFF25U:
      value = 0xFFU;
      break;

    /* TODO: Audio - Sound on/off */
    case 0xFF26U:
      value = 0xFFU;
      break;

    case 0xFF27U:
    case 0xFF28U:
    case 0xFF29U:
    case 0xFF2AU:
    case 0xFF2BU:
    case 0xFF2CU:
    case 0xFF2DU:
    case 0xFF2EU:
    case 0xFF2FU:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    /* TODO: Audio - Wave pattern RAM */
    case 0xFF30U:
    case 0xFF31U:
    case 0xFF32U:
    case 0xFF33U:
    case 0xFF34U:
    case 0xFF35U:
    case 0xFF36U:
    case 0xFF37U:
    case 0xFF38U:
    case 0xFF39U:
    case 0xFF3AU:
    case 0xFF3BU:
    case 0xFF3CU:
    case 0xFF3DU:
    case 0xFF3EU:
    case 0xFF3FU:
      value = 0xFFU;
      break;

    case 0xFF40U:
      value = gameboy->get_ppu().get_lcd_lcdc().get();
      break;

    case 0xFF41U:
      value = gameboy->get_ppu().get_lcd_stat().get();
      break;

    case 0xFF42U:
      value = gameboy->get_ppu().get_tile_scy().get();
      break;

    case 0xFF43U:
      value = gameboy->get_ppu().get_tile_scx().get();
      break;

    case 0xFF44U:
      value = gameboy->get_ppu().get_lcd_ly().get();
      break;

    case 0xFF45U:
      value = gameboy->get_ppu().get_lcd_lyc().get();
      break;

    case 0xFF46U:
      log_warn("Unimplemented warning, attempted to read from write-only DMA Transfer/Start Address (0xFF46)\r\n");
      value = 0xFFU;
      break;

    case 0xFF47U:
      value = gameboy->get_ppu().get_tile_bgp().get();
      break;

    case 0xFF48U:
      value = gameboy->get_ppu().get_sprite_obp0().get();
      break;

    case 0xFF49U:
      value = gameboy->get_ppu().get_sprite_obp1().get();
      break;

    case 0xFF4AU:
      value = gameboy->get_ppu().get_tile_wy().get();
      break;

    case 0xFF4BU:
      value = gameboy->get_ppu().get_tile_wx().get();
      break;

    /* TODO: CGB mode behaviour */
    case 0xFF4CU:
      value = 0xFFU;
      break;

    case 0xFF4DU:
      log_warn("Unimplemented warning, attempted to read from 'Prepare Speed Switch' register\r\n");
      value = 0U;
      break;

    case 0xFF4EU:
    case 0xFF4FU:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    case 0xFF50U:
      value = disable_boot_rom_switch.get();
      break;

    case 0xFF51U:
      log_warn("Unimplemented warning, attempted to read from VRAM DMA Source (hi)\r\n");
      value = 0xFFU;
      break;

    case 0xFF52U:
      log_warn("Unimplemented warning, attempted to read from VRAM DMA Source (lo)\r\n");
      value = 0xFFU;
      break;

    case 0xFF53U:
      log_warn("Unimplemented warning, attempted to read from VRAM DMA Destination (hi)\r\n");
      value = 0xFFU;
      break;

    case 0xFF54U:
      log_warn("Unimplemented warning, attempted to read from VRAM DMA Destination (lo)\r\n");
      value = 0xFFU;
      break;

    case 0xFF55U:
      log_warn("Unimplemented warning, attempted to read from VRAM DMA Length/Mode/Start\r\n");
      value = 0xFFU;
      break;

    case 0xFF56U:
      log_warn("Unimplemented warning, attempted to read from infrared port\r\n");
      value = 0xFFU;
      break;

    case 0xFF57U:
    case 0xFF58U:
    case 0xFF59U:
    case 0xFF5AU:
    case 0xFF5BU:
    case 0xFF5CU:
    case 0xFF5DU:
    case 0xFF5EU:
    case 0xFF5FU:
    case 0xFF60U:
    case 0xFF61U:
    case 0xFF62U:
    case 0xFF63U:
    case 0xFF64U:
    case 0xFF65U:
    case 0xFF66U:
    case 0xFF67U:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    /* TODO: Background color palette spec/index */
    case 0xFF68U:
      log_warn("Unimplemented warning, attempted to read from CGB background color palette spec/index\r\n");
      value = 0xFFU;
      break;

    /* TODO: Background color palette data */
    case 0xFF69U:
      log_warn("Unimplemented warning, attempted to read from CGB background color data\r\n");
      value = 0xFFU;
      break;

    /* TODO: OBJ color palette spec/index */
    case 0xFF6AU:
      log_warn("Unimplemented warning, attempted to read from CGB OBJ color palette spec/index\r\n");
      value = 0xFFU;
      break;

    /* TODO: OBJ color palette data */
    case 0xFF6BU:
      log_warn("Unimplemented warning, attempted to read from CGB OBJ color palette data\r\n");
      value = 0xFFU;
      break;

    /* TODO: Object priority mode */
    case 0xFF6CU:
      log_warn("Unimplemented warning, attempted to read from CGB object priority mode\r\n");
      value = 0xFFU;
      break;

    case 0xFF6DU:
    case 0xFF6EU:
    case 0xFF6FU:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    /* TODO: CGB WRAM bank */
    case 0xFF70U:
      log_warn("Unimplemented warning, attempted to read from CGB WRAM bank\r\n");
      value = 0xFFU;
      break;

    /* TODO: Some undocumented registers in this range */
    case 0xFF71U:
    case 0xFF72U:
    case 0xFF73U:
    case 0xFF74U:
    case 0xFF75U:
    case 0xFF76U:
    case 0xFF77U:
    case 0xFF78U:
    case 0xFF79U:
    case 0xFF7AU:
    case 0xFF7BU:
    case 0xFF7CU:
    case 0xFF7DU:
    case 0xFF7EU:
    case 0xFF7FU:
      log_warn("Unimplemented warning, attempting to read from unused IO address 0x%x\r\n", address);
      value = 0xFFU;
      break;

    default:
      log_error("Unmapped IO address: 0x%x\r\n", address);
      value = 0xFFU;
      break;
  }

  return value;
}

void MemoryController::write(const Address address, u8 byte) {
  /* Cartridge ROM memory */
  if (MEMORY_IN_RANGE(address, 0x0000U, 0x7FFFU)) {
    gameboy->get_cartridge().writeROM(address, byte);
  }

  /* VRAM */
  else if (MEMORY_IN_RANGE(address, 0x8000U, 0x9FFFU)) {
    vram.at(address - 0x8000U) = byte;
  }

  /* Cartridge RAM */
  else if (MEMORY_IN_RANGE(address, 0xA000U, 0xBFFFU)) {
    gameboy->get_cartridge().writeRAM(address, byte);
  }

  /* WRAM Bank  */
  else if (MEMORY_IN_RANGE(address, 0xC000U, 0xDFFFU)) {
    work_ram.at(address - 0xC000U) = byte;
  }

  /* Echo RAM */
  else if (MEMORY_IN_RANGE(address, 0xE000U, 0xFDFFU)) {
    write(address - 0x2000U, byte);
  }

  /* OAM */
  else if (MEMORY_IN_RANGE(address, 0xFE00U, 0xFE9FU)) {
    oam_ram.at(address - 0xFE00U) = byte;
  }

  /* Reserved */
  else if (MEMORY_IN_RANGE(address, 0xFEA0U, 0xFEFFU)) {
  }

  /* I/O Registers */
  else if (MEMORY_IN_RANGE(address, 0xFF00U, 0xFF7FU)) {
    write_io(address, byte);
  }

  /* High RAM */
  else if (MEMORY_IN_RANGE(address, 0xFF80U, 0xFFFEU)) {
    high_ram.at(address - 0xFF80U) = byte;
  }

  /* Interrupt Enable register */
  else if (address == 0xFFFF) {
    gameboy->get_cpu().interrupt_enabled_reg.set(byte);
  }

  else {
  }
}

void MemoryController::write_io(const Address address, u8 byte) {
  switch (address) {
    case 0xFF00U:
      gameboy->get_input().write(byte);
      break;

    case 0xFF01U:
      /* Serial data transfer (SB) */
      gameboy->get_serial().write(byte);
      break;

    case 0xFF02U:
      /* Serial data transfer (SB) */
      gameboy->get_serial().write_control(byte);
      break;

    case 0xFF03U:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    case 0xFF04U:
      gameboy->get_timer().reset_divider();
      break;

    case 0xFF05U:
      gameboy->get_timer().set_timer_counter(byte);
      break;

    case 0xFF06U:
      gameboy->get_timer().set_timer_counter_modulo(byte);
      break;

    case 0xFF07U:
      gameboy->get_timer().set_timer_counter_control(byte);
      break;

    case 0xFF08U:
    case 0xFF09U:
    case 0xFF0AU:
    case 0xFF0BU:
    case 0xFF0CU:
    case 0xFF0DU:
    case 0xFF0EU:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    case 0xFF0FU:
      gameboy->get_cpu().interrupt_flag.set(byte);
      break;

    /* TODO: Audio - Channel 1U: Tone & Sweep */
    case 0xFF10U:
    case 0xFF11U:
    case 0xFF12U:
    case 0xFF13U:
    case 0xFF14U:
      break;

    case 0xFF15U:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    /* TODO: Audio - Channel 2U: Tone */
    case 0xFF16U:
    case 0xFF17U:
    case 0xFF18U:
    case 0xFF19U:
      break;

    /* TODO: Audio - Channel 3U: Wave Output */
    case 0xFF1AU:
    case 0xFF1BU:
    case 0xFF1CU:
    case 0xFF1DU:
    case 0xFF1EU:
      break;

    case 0xFF1FU:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    /* TODO: Audio - Channel 4U: Noise */
    case 0xFF20U:
    case 0xFF21U:
    case 0xFF22U:
    case 0xFF23U:
      break;

    /* TODO: Audio - Channel control/ON-OFF/Volume */
    case 0xFF24U:
      break;

    /* TODO: Audio - Selection of sound output terminal */
    case 0xFF25U:
      break;

    /* TODO: Audio - Sound on/off */
    case 0xFF26U:
      log_warn("Wrote to sound on/off address 0x%x - 0x%x\r\n", address, byte);
      break;

    case 0xFF27U:
    case 0xFF28U:
    case 0xFF29U:
    case 0xFF2AU:
    case 0xFF2BU:
    case 0xFF2CU:
    case 0xFF2DU:
    case 0xFF2EU:
    case 0xFF2FU:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    /* TODO: Audio - Wave pattern RAM */
    case 0xFF30U:
    case 0xFF31U:
    case 0xFF32U:
    case 0xFF33U:
    case 0xFF34U:
    case 0xFF35U:
    case 0xFF36U:
    case 0xFF37U:
    case 0xFF38U:
    case 0xFF39U:
    case 0xFF3AU:
    case 0xFF3BU:
    case 0xFF3CU:
    case 0xFF3DU:
    case 0xFF3EU:
    case 0xFF3FU:
      break;

    /* Switch on LCD */
    case 0xFF40U:
      log_debug("Writing to lcd control register: %u\r\n", byte);
      gameboy->get_ppu().get_lcd_lcdc().set(byte);
      break;

    case 0xFF41U:
      gameboy->get_ppu().get_lcd_stat().set(byte);
      break;

    /* Vertical Scroll Register */
    case 0xFF42U:
      gameboy->get_ppu().get_tile_scy().set(byte);
      break;

    /* Horizontal Scroll Register */
    case 0xFF43U:
      gameboy->get_ppu().get_tile_scx().set(byte);
      break;

    /* LY - Line Y coordinate */
    case 0xFF44U:
      /* "Writing will reset the counter */
      gameboy->get_ppu().get_lcd_ly().set(0x0);
      break;

    case 0xFF45U:
      gameboy->get_ppu().get_lcd_lyc().set(byte);
      break;

    case 0xFF46U:
      dma_transfer(byte);
      break;

    case 0xFF47U:
      gameboy->get_ppu().get_tile_bgp().set(byte);
      log_trace("Set video palettEU: 0x%x\r\n", byte);
      break;

    case 0xFF48U:
      gameboy->get_ppu().get_sprite_obp0().set(byte);
      log_trace("Set sprite palette 0U: 0x%x\r\n", byte);
      break;

    case 0xFF49U:
      gameboy->get_ppu().get_sprite_obp1().set(byte);
      log_trace("Set sprite palette 1U: 0x%x\r\n", byte);
      break;

    case 0xFF4AU:
      gameboy->get_ppu().get_tile_wx().set(byte);
      break;

    case 0xFF4BU:
      gameboy->get_ppu().get_tile_wy().set(byte);
      break;

    /* TODO: CGB mode behaviour */
    case 0xFF4CU:
      break;

    case 0xFF4DU:
      log_warn("Unimplemented warning, attempted to write to 'Prepare Speed Switch' register\r\n");
      break;

    case 0xFF4EU:
    case 0xFF4FU:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    /* Disable boot rom switch */
    case 0xFF50U:
      disable_boot_rom_switch.set(byte);
      log_debug("Boot rom was disabled\r\n");
      break;

    case 0xFF51U:
      log_warn("Unimplemented warning, attempted to write to VRAM DMA Source (hi)\r\n");
      break;

    case 0xFF52U:
      log_warn("Unimplemented warning, attempted to write to VRAM DMA Source (lo)\r\n");
      break;

    case 0xFF53U:
      log_warn("Unimplemented warning, attempted to write to VRAM DMA Destination (hi)\r\n");
      break;

    case 0xFF54U:
      log_warn("Unimplemented warning, attempted to write to VRAM DMA Destination (lo)\r\n");
      break;

    case 0xFF55U:
      log_warn("Unimplemented warning, attempted to write to VRAM DMA Length/Mode/Start\r\n");
      break;

    case 0xFF56U:
      log_warn("Unimplemented warning, attempted to write to infrared port\r\n");
      break;

    case 0xFF57U:
    case 0xFF58U:
    case 0xFF59U:
    case 0xFF5AU:
    case 0xFF5BU:
    case 0xFF5CU:
    case 0xFF5DU:
    case 0xFF5EU:
    case 0xFF5FU:
    case 0xFF60U:
    case 0xFF61U:
    case 0xFF62U:
    case 0xFF63U:
    case 0xFF64U:
    case 0xFF65U:
    case 0xFF66U:
    case 0xFF67U:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    /* TODO: Background color palette spec/index */
    case 0xFF68U:
      log_warn("Unimplemented warning, attempted to write to CGB background color palette spec/index\r\n");
      break;

    /* TODO: Background color palette data */
    case 0xFF69U:
      log_warn("Unimplemented warning, attempted to write to CGB background color data\r\n");
      break;

    /* TODO: OBJ color palette spec/index */
    case 0xFF6AU:
      log_warn("Unimplemented warning, attempted to write to CGB OBJ color palette spec/index\r\n");
      break;

    /* TODO: OBJ color palette data */
    case 0xFF6BU:
      log_warn("Unimplemented warning, attempted to write to CGB OBJ color palette data\r\n");
      break;

    /* TODO: Object priority mode */
    case 0xFF6CU:
      log_warn("Unimplemented warning, attempted to write to CGB object priority mode\r\n");
      break;

    case 0xFF6DU:
    case 0xFF6EU:
    case 0xFF6FU:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    /* TODO: CGB WRAM bank */
    case 0xFF70U:
      log_warn("Unimplemented warning, attempted to write to CGB WRAM bank\r\n");
      break;

    /* TODO: Some undocumented registers in this range */
    case 0xFF71U:
    case 0xFF72U:
    case 0xFF73U:
    case 0xFF74U:
    case 0xFF75U:
    case 0xFF76U:
    case 0xFF77U:
    case 0xFF78U:
    case 0xFF79U:
    case 0xFF7AU:
    case 0xFF7BU:
    case 0xFF7CU:
    case 0xFF7DU:
    case 0xFF7EU:
    case 0xFF7FU:
      log_warn("Unimplemented warning, attempting to write to unused IO address 0x%x - 0x%x\r\n", address, byte);
      break;

    default:
      log_error("Unmapped IO address: 0x%x\r\n", address);
      break;
  }
}

bool MemoryController::boot_rom_active() {
  return (read(0xFF50U) != 0x1U);
}

void MemoryController::dma_transfer(u8 byte) {
  Address start_address = byte * 0x100U;

  for (u8 i = 0x0; i <= 0x9FU; i++) {
    Address from_address = start_address + i;
    Address to_address = 0xFE00U + i;

    u8 value_at_address = read(from_address);
    write(to_address, value_at_address);
  }
  
  log_debug("Dma transfer\r\n");
}

void MemoryController::set_gameboy(Gameboy *gb) {
  this->gameboy = gb;
}
