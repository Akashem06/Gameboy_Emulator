#include "common.hpp"
#include <vector>

/*--------------------- CATRIDGE ROM ---------------------*/
/* 0x0000 - 0x3FFF : ROM Bank 0. */
/* 0x4000 - 0x7FFF : ROM Bank 1 - Switchable. */

/*--------------------- VRAM SECTION ---------------------*/
/* 0x8000 - 0x97FF : CHR RAM */
/* 0x9800 - 0x9BFF : BG Map 1 */
/* 0x9C00 - 0x9FFF : BG Map 2 */

/*--------------------- CATRIDGE RAM ---------------------*/
/* 0xA000 - 0xBFFF : Cartridge RAM */
/* 0xC000 - 0xCFFF : WRAM Bank 0 */
/* 0xD000 - 0xDFFF : WRAM Bank 1-7 - switchable - Color only */

/*----------------------- RESERVED -----------------------*/
/* 0xE000 - 0xFDFF : Echo RAM */
/* 0xFE00 - 0xFE9F : Object Attribute Memory */
/* 0xFEA0 - 0xFEFF : Reserved - Unusable */

/*--------------------- IO REGISTERS ---------------------*/
/* 0xFF00 - 0xFF7F : I/O Registers */
/* 0xFF80 - 0xFFFE : Zero Page */

#define MEMORY_IN_RANGE(address, lower, upper) (address >= lower && address <= upper? true : false)

using Address = u16;

class MemoryController {
    private:
        std::vector<u8> work_ram;
        std::vector<u8> oam_ram;
        std::vector<u8> high_ram;
    public:
        MemoryController();
        u8 read(const Address address);
        void write(const Address address, u8 byte);
};
