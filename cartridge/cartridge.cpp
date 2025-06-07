#include "cartridge.hpp"

#include "files.hpp"
#include "log.hpp"

static std::string s_getTitle(std::vector<u8> &rom_data) {
  char name[CARTRIDGE_TITLE_LENGTH] = { 0U };
  for (u8 i = 0U; i < CARTRIDGE_TITLE_LENGTH; i++) {
    name[i] = static_cast<char>(rom_data[CartridgeHeader::title + i]);
  }
  return name;
}

static CartridgeType s_getType(std::vector<u8> &rom_data) {
  CartridgeType type = CartridgeType::UNKNOWN;

  switch (rom_data[CartridgeHeader::cartridge_type]) {
    case 0x00U:
      type = CartridgeType::ROM_ONLY;
      break;
    case 0x01U:
      type = CartridgeType::MBC1;
      break;
    case 0x02U:
      type = CartridgeType::MBC1__RAM;
      break;
    case 0x03U:
      type = CartridgeType::MCB1__RAM__BATT;
      break;
    case 0x05U:
      type = CartridgeType::MBC2;
      break;
    case 0x06U:
      type = CartridgeType::MCB2__BATTERY;
      break;
    case 0x08U:
      type = CartridgeType::ROM__RAM;
      break;
    case 0x09U:
      type = CartridgeType::ROM__RAM__BATT;
      break;
    case 0x0BU:
      type = CartridgeType::MMM01;
      break;
    case 0x0CU:
      type = CartridgeType::MMM01__RAM;
      break;
    case 0x0DU:
      type = CartridgeType::MMM01__RAM__BATT;
      break;
    case 0x0FU:
      type = CartridgeType::MCB3__TIMER__BATT;
      break;
    case 0x10U:
      type = CartridgeType::MCB3__TIMER__RAM__BATT;
      break;
    case 0x11U:
      type = CartridgeType::MBC3;
      break;
    case 0x12U:
      type = CartridgeType::MCB3__RAM;
      break;
    case 0x13U:
      type = CartridgeType::MCB3__RAM__BATT;
      break;
    case 0x19U:
      type = CartridgeType::MBC5;
      break;
    case 0x1AU:
      type = CartridgeType::MCB5__RAM;
      break;
    case 0x1BU:
      type = CartridgeType::MCB5__RAM__BATT;
      break;
    case 0x1CU:
      type = CartridgeType::MCB5__RUMBLE;
      break;
    case 0x1DU:
      type = CartridgeType::MCB5__RUMBLE__RAM;
      break;
    case 0x1EU:
      type = CartridgeType::MCB5__RUMBLE__RAM__BATT;
      break;
    case 0x20U:
      type = CartridgeType::MCB6;
      break;
    case 0x22U:
      type = CartridgeType::MCB7__SENSOR__RUMBLE__RAM__BATT;
      break;
    default:
      type = CartridgeType::UNKNOWN;
      break;
  }

  return type;
}

static Destination s_getDestination(std::vector<u8> &rom_data) {
  Destination dest = Destination::UNKNOWN;

  switch (rom_data[CartridgeHeader::destination_code]) {
    case 0x00U:
      dest = Destination::JAPANESE;
      break;
    case 0x01U:
      dest = Destination::NON_JAPANESE;
      break;
    default:
      dest = Destination::UNKNOWN;
      break;
  }

  return dest;
}

static ROMSize s_getROMSize(std::vector<u8> &rom_data) {
  ROMSize rom_size = ROMSize::UNKNOWN;

  switch (rom_data[CartridgeHeader::rom_size]) {
    case 0x00U:
      rom_size = ROMSize::SIZE_32KB;
      break;
    case 0x01U:
      rom_size = ROMSize::SIZE_64KB;
      break;
    case 0x02U:
      rom_size = ROMSize::SIZE_128KB;
      break;
    case 0x03U:
      rom_size = ROMSize::SIZE_256KB;
      break;
    case 0x04U:
      rom_size = ROMSize::SIZE_512KB;
      break;
    case 0x05U:
      rom_size = ROMSize::SIZE_1MB;
      break;
    case 0x06U:
      rom_size = ROMSize::SIZE_2MB;
      break;
    case 0x07U:
      rom_size = ROMSize::SIZE_4MB;
      break;
    case 0x08U:
      rom_size = ROMSize::SIZE_8MB;
      break;
    case 0x52U:
      rom_size = ROMSize::SIZE_1p1MB;
      break;
    case 0x53U:
      rom_size = ROMSize::SIZE_1p2MB;
      break;
    case 0x54U:
      rom_size = ROMSize::SIZE_1p5MB;
      break;
    default:
      rom_size = ROMSize::UNKNOWN;
      break;
  }

  return rom_size;
}

static RAMSize s_getRAMSize(std::vector<u8> &rom_data) {
  RAMSize ram_size = RAMSize::UNKNOWN;

  switch (rom_data[CartridgeHeader::ram_size]) {
    case 0x00U:
      ram_size = RAMSize::NONE;
      break;
    case 0x02U:
      ram_size = RAMSize::SIZE_8KB;
      break;
    case 0x03U:
      ram_size = RAMSize::SIZE_32KB;
      break;
    case 0x04U:
      ram_size = RAMSize::SIZE_128KB;
      break;
    case 0x05U:
      ram_size = RAMSize::SIZE_64KB;
      break;
  }

  return ram_size;
}

static bool s_checkHeaderChecksum(std::vector<u8> &rom_data) {
  uint8_t header_checksum = rom_data[CartridgeHeader::header_checksum];
  uint8_t calculated_checksum = 0U;
  for (uint16_t address = 0x0134U; address <= 0x014CU; address++) {
    calculated_checksum = calculated_checksum - rom_data[address] - 1;
  }

  if (header_checksum != calculated_checksum) {
    return false;
  }

  return true;
}

u32 Cartridge::getRAMByteSize() const {
  switch (ram_size) {
    case RAMSize::SIZE_2KB:
      return 2U * 1024U;
    case RAMSize::SIZE_8KB:
      return 8U * 1024U;
    case RAMSize::SIZE_32KB:
      return 32U * 1024U;
    case RAMSize::SIZE_64KB:
      return 64U * 1024U;
    case RAMSize::SIZE_128KB:
      return 128U * 1024U;
    default:
      return 0U;
  }
}

Cartridge::Cartridge() {
  title = "";
  type = CartridgeType::UNKNOWN;
  destination = Destination::UNKNOWN;
  rom_size = ROMSize::UNKNOWN;
  ram_size = RAMSize::UNKNOWN;
  header_checksum = 0U;
  supports_cgb = false;
  supports_sgb = false;
};

bool Cartridge::readInfo(const std::string &filename) {
  File::read_file(filename, rom_data);

  if (!s_checkHeaderChecksum(rom_data)) {
    log_error("Invalid header checksum.\n");
  }

  title = s_getTitle(rom_data);
  type = s_getType(rom_data);
  destination = s_getDestination(rom_data);
  rom_size = s_getROMSize(rom_data);
  ram_size = s_getRAMSize(rom_data);

  supports_cgb = rom_data[CartridgeHeader::cgb_flag] == 0x80U || rom_data[CartridgeHeader::cgb_flag] == 0xC0U ? true : false;
  supports_sgb = rom_data[CartridgeHeader::sgb_flag] == 0x03U ? true : false;

  ram_banks.resize(getRAMByteSize(), 0U);

  log_debug("Name: %s\n\r", title.c_str());
  log_debug("Type: %d\n", (int)type);
  log_debug("Rom size: %d\n", (int)rom_size);
  log_debug("Ram size: %d\n", (int)ram_size);

  return true;
}

u8 Cartridge::readROM(const Address address) {
  if (MEMORY_IN_RANGE(address, 0U, 0x3FFFU)) {
    return rom_data[address];
  } else if (MEMORY_IN_RANGE(address, 0x4000U, 0x7FFFU)) {
    u16 banked_address = (current_rom_bank * 0x4000U) + (address - 0x4000U);

    if (banked_address < rom_data.size()) {
      return rom_data[banked_address];
    }
  }

  return 0xFFU;
}

void Cartridge::writeROM(const Address address, u8 byte) {
  switch (type) {
    case CartridgeType::MBC1:
    case CartridgeType::MBC1__RAM:
    case CartridgeType::MCB1__RAM__BATT:
      if (MEMORY_IN_RANGE(address, 0, 0x2000U)) {
        ram_enabled = (byte & 0x0F) == 0x0A;
      } else if (MEMORY_IN_RANGE(address, 0x2000U, 0x4000U)) {
        current_rom_bank = byte & 0x1F;

        // ROM bank 0 is not allowed
        if (current_rom_bank == 0) {
          current_rom_bank = 1;
        }

      } else if (MEMORY_IN_RANGE(address, 0x4000U, 0x6000U)) {
        current_ram_bank = byte & 0x03;
      }
      break;

    default:
      break;
  }
}

u8 Cartridge::readRAM(const Address address) {
  if (!ram_enabled || ram_banks.empty()) {
    return 0xFFU;
  }

  u16 ram_address = (current_ram_bank * 0x2000U) + (address - 0xA000U);

  if (MEMORY_IN_RANGE(address, 0xA000U, 0xC000U) && ram_address < ram_banks.size()) {
    return ram_banks[ram_address];
  }

  return 0xFFU;
}

void Cartridge::writeRAM(const Address address, u8 byte) {
  if (!ram_enabled || ram_banks.empty()) {
    return;
  }

  u16 ram_address = (current_ram_bank * 0x2000U) + (address - 0xA000U);

  if (MEMORY_IN_RANGE(address, 0xA000U, 0xC000U) && ram_address < ram_banks.size()) {
    ram_banks[ram_address] = byte;
  }
}
