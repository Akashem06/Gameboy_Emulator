#include "memory_controller.hpp"

#include "gameboy.hpp"

MemoryController::MemoryController(CPU *cpu, Cartridge *cartridge) {
  cpu = cpu;
  cartridge = cartridge;
  work_ram = std::vector<u8>(0x2000U);
  oam_ram = std::vector<u8>(0x00A0U);
  high_ram = std::vector<u8>(0x80U);
}

u8 MemoryController::read(const Address address) {
  u8 value = 0U;

  /* Cartridge ROM memory */
  if (MEMORY_IN_RANGE(address, 0x0000U, 0x7FFFU)) {
    value = cartridge->readROM(address);
  }
  /* VRAM */
  else if (MEMORY_IN_RANGE(address, 0x8000U, 0x9FFFU)) {
  }

  /* Cartridge RAM */
  else if (MEMORY_IN_RANGE(address, 0xA000U, 0xBFFFU)) {
    value = cartridge->readRAM(address);
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
  else if (MEMORY_IN_RANGE(address, 0xFEA0U, 0xFF7FU)) {
    value = read_io(address);
  }

  /* High RAM */
  else if (MEMORY_IN_RANGE(address, 0xFF80U, 0xFFFEU)) {
    value = high_ram.at(address - 0xFF80U);
  }

  /* Interrupt Enable Register */
  else if (address == 0xFFFFU) {
    value = cpu->interrupt_enabled_reg.get();
  }

  /* Invalid address */
  else {
  }

  return value;
}

u8 MemoryController::read_io(const Address address) {}

void MemoryController::write(const Address address, u8 byte) {
  /* Cartridge ROM memory */
  if (MEMORY_IN_RANGE(address, 0x0000U, 0x7FFFU)) {
    cartridge->writeROM(address, byte);
  }

  /* VRAM */
  else if (MEMORY_IN_RANGE(address, 0x8000U, 0x9FFFU)) {
    // video.write(address - 0x8000U, byte);
  }

  /* Cartridge RAM */
  else if (MEMORY_IN_RANGE(address, 0xA000U, 0xBFFFU)) {
    cartridge->writeRAM(address, byte);
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
    cpu->interrupt_enabled_reg.set(byte);
  }

  else {
  }
}

void MemoryController::write_io(const Address address, u8 byte) {}
