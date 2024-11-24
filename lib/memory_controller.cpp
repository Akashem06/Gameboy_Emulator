#include "memory_controller.hpp"

MemoryController::MemoryController() {
    work_ram = std::vector<u8>(0x2000U);
    oam_ram = std::vector<u8>(0x00A0U);
    high_ram = std::vector<u8>(0x80U);
}

u8 MemoryController::read(const Address address) {
    u8 value = 0U;

    if(MEMORY_IN_RANGE(address, 0x0000U,  0x7FFFU)) {

    }
    /* VRAM */
    else if(MEMORY_IN_RANGE(address, 0x8000U,  0x9FFFU)) {

    }

    /* Cartridge RAM */
    else if(MEMORY_IN_RANGE(address, 0xA000U,  0xBFFFU)) {

    }

    /* WRAM Bank  */
    else if(MEMORY_IN_RANGE(address, 0xC000U,  0xDFFFU)) {
        value = work_ram.at(address - 0xC000U);
    }

    /* Echo RAM */
    else if(MEMORY_IN_RANGE(address, 0xE000U,  0xFDFFU)) {

    }

    /* OAM */
    else if(MEMORY_IN_RANGE(address, 0xFE00U,  0xFE9FU)) {
        value = oam_ram.at(address - 0xFE00U);
    }

    /* Reserved */
    else if(MEMORY_IN_RANGE(address, 0xFEA0U,  0xFEFFU)) {

    }

    /* I/O Registers */
    else if(MEMORY_IN_RANGE(address, 0xFEA0U,  0xFF7FU)) {

    }

    /* High RAM */
    else if(MEMORY_IN_RANGE(address, 0xFF80U,  0xFFFEU)) {
        value = high_ram.at(address - 0xFF80U);
    }

    /* Interrupt Enable Register */
    else if (address == 0xFFFFU) {

    }

    /* Invalid address */
    else {
        
    }

    return value;
}

void MemoryController::write(const Address address, u8 byte) {
    
}
