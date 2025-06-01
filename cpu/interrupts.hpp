#include "common.hpp"

/* All hardware interrupts available in the gameboy */
namespace interrupts {
const u16 vblank = 0x40U;
const u16 lcdc_status = 0x48U;
const u16 timer = 0x50U;
const u16 serial = 0x58U;
const u16 joypad = 0x60U;
}  // namespace interrupts

namespace interrupt_flags {
const u8 vblank = 1U << 0U;      /**< 0x01 */
const u8 lcdc_status = 1U << 1U; /**< 0x02 */
const u8 timer = 1U << 2U;       /**< 0x04 */
const u8 serial = 1U << 3U;      /**< 0x08 */
const u8 joypad = 1U << 4U;      /**< 0x10 */
}  // namespace interrupt_flags
