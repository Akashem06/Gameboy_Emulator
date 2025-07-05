#pragma once

#include <string>
#include <vector>

#include "common.hpp"
#include "mem.h"

#ifndef CARTRIDGE_TITLE_LENGTH
#define CARTRIDGE_TITLE_LENGTH 15U
#endif

class Gameboy;

namespace CartridgeHeader {
const int entry_point = 0x100U;
const int logo = 0x104U;
const int title = 0x134U;
const int manufacturer_code = 0x13FU;
const int cgb_flag = 0x143U;
const int new_license_code = 0x144U;
const int sgb_flag = 0x146U;
const int cartridge_type = 0x147U;
const int rom_size = 0x148U;
const int ram_size = 0x149U;
const int destination_code = 0x14AU;
const int old_license_code = 0x14BU;
const int version_number = 0x14CU;
const int header_checksum = 0x14DU;
const int global_checksum = 0x14EU;
}  // namespace CartridgeHeader

enum class CartridgeType {
  ROM_ONLY,
  ROM__RAM,
  ROM__RAM__BATT,
  MMM01,
  MMM01__RAM,
  MMM01__RAM__BATT,
  MBC1,
  MBC1__RAM,
  MCB1__RAM__BATT,
  MBC2,
  MCB2__BATTERY,
  MBC3,
  MCB3__RAM,
  MCB3__RAM__BATT,
  MCB3__TIMER__BATT,
  MCB3__TIMER__RAM__BATT,
  MBC5,
  MCB5__RAM,
  MCB5__RAM__BATT,
  MCB5__RUMBLE,
  MCB5__RUMBLE__RAM,
  MCB5__RUMBLE__RAM__BATT,
  MCB6,
  MCB7__SENSOR__RUMBLE__RAM__BATT,
  UNKNOWN
};

enum class Destination { JAPANESE, NON_JAPANESE, UNKNOWN };

enum class ROMSize {
  SIZE_32KB,
  SIZE_64KB,
  SIZE_128KB,
  SIZE_256KB,
  SIZE_512KB,
  SIZE_1MB,
  SIZE_2MB,
  SIZE_4MB,
  SIZE_8MB,
  SIZE_1p1MB,
  SIZE_1p2MB,
  SIZE_1p5MB,
  UNKNOWN
};

enum class RAMSize { NONE, SIZE_2KB, SIZE_8KB, SIZE_32KB, SIZE_64KB, SIZE_128KB, UNKNOWN };

class Cartridge {
 private:
  Gameboy *gameboy = nullptr;
  std::vector<u8> rom_data;
  std::vector<u8> ram_banks;

  std::string title;
  CartridgeType type;
  Destination destination;
  ROMSize rom_size;
  RAMSize ram_size;

  uint16_t header_checksum;

  bool supports_cgb;
  bool supports_sgb;

  u8 current_rom_bank;
  u8 current_ram_bank;
  bool ram_enabled;

  u32 getRAMByteSize() const;

 public:
  Cartridge();

  bool readInfo(const std::string &filename);

  u8 readROM(const Address address);
  void writeROM(const Address address, u8 byte);

  u8 readRAM(const Address address);
  void writeRAM(const Address address, u8 byte);

  void set_gameboy(Gameboy *gb);
};
