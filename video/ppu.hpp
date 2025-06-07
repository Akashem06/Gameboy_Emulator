#pragma once

#include "common.hpp"
#include "framebuffer.hpp"
#include "memory_controller.hpp"
class PPU {
 private:
  const u16 CLOCKS_PER_HBLANK = 204;        /**< Mode 0 */
  const u16 CLOCKS_PER_VBLANK = 4560;       /**< Mode 1 */
  const u16 CLOCKS_PER_SCANLINE_OAM = 80;   /**< Mode 2 */
  const u16 CLOCKS_PER_SCANLINE_VRAM = 172; /**< Mode 3 */
  const u16 CLOCKS_PER_SCANLINE = (CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK);

  const u16 SCANLINES_PER_FRAME = 144;
  const u16 CLOCKS_PER_FRAME = (CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME) + CLOCKS_PER_VBLANK;

  enum class Mode {
    HBLANK,        /**< */
    VBLANK,        /**< */
    OAM_SEARCH,    /**< */
    PIXEL_TRANSFER /**< */
  };

  void oam_search();
  void pixel_transfer();
  void hblank();
  void vblank();
  void update_mode();

  MemoryController *mem_ctrl;
  Framebuffer framebuffer;
  Mode current_mode;
  u16 mode_clock;
  u8 current_line;
  u32 current_scanline;

 public:
  explicit PPU(MemoryController *mem_ctrl);

  void tick();
  void reset();
};