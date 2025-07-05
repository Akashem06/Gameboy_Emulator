#pragma once

#include "common.hpp"

/* All hardware interrupts available in the gameboy */
namespace interrupts {
enum class vector : u16 {
  vblank = 0x40U,
  lcdc_status = 0x48U,
  timer = 0x50U,
  serial = 0x58U,
  joypad = 0x60U,
};

enum class flags : u8 {
  vblank = 1U << 0U,      /**< 0x01 */
  lcdc_status = 1U << 1U, /**< 0x02 */
  timer = 1U << 2U,       /**< 0x04 */
  serial = 1U << 3U,      /**< 0x08 */
  joypad = 1U << 4U,      /**< 0x10 */
};
}  // namespace interrupts
