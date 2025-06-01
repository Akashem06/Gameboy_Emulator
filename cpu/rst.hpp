#include "common.hpp"

/* RST commands are similar to software interrupts, where they jump to predefined memory addresses
 */
namespace rst {
enum class vector : u16 {
  rst_0x00 = 0x00U,
  rst_0x08 = 0x08U,
  rst_0x10 = 0x10U,
  rst_0x18 = 0x18U,
  rst_0x20 = 0x20U,
  rst_0x28 = 0x28U,
  rst_0x30 = 0x30U,
  rst_0x38 = 0x38U
};
}
