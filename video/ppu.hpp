#pragma once

#include "common.hpp"
#include "framebuffer.hpp"
#include "lcd_controller.hpp"
#include "memory_controller.hpp"
#include "sprite_renderer.hpp"
#include "tile_renderer.hpp"

class Gameboy;

class PPU {
 private:
  Gameboy *gameboy = nullptr;

  const u16 CLOCKS_PER_HBLANK = 204;
  const u16 CLOCKS_PER_SCANLINE_OAM = 80;
  const u16 CLOCKS_PER_SCANLINE_VRAM = 172;
  const u16 CLOCKS_PER_SCANLINE = CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK;

  const u16 VBLANK_SCANLINES = 10;
  const u16 VISIBLE_SCANLINES = 144;
  const u16 SCANLINES_PER_FRAME = VISIBLE_SCANLINES + VBLANK_SCANLINES;

const u16 VBLANK_START_LINE = 144;
const u16 VBLANK_END_LINE = 153;

  const u16 CLOCKS_PER_FRAME = CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME;

  enum class Mode {
    HBLANK,        /**< */
    VBLANK,        /**< */
    OAM_SEARCH,    /**< */
    PIXEL_TRANSFER /**< */
  };

  void set_mode(Mode mode);
  void render_scanline();

  Mode current_mode;
  u16 mode_clock;
  u8 current_line;
  u32 current_scanline;

  LCDController lcd;
  TileRenderer tile_renderer;
  SpriteRenderer sprite_renderer;
  Framebuffer framebuffer;

 public:
  explicit PPU();

  void tick(int cycles);

  void step();
  void reset();

  void request_vblank_interrupt();
  void request_lcd_interrupt();

  void set_gameboy(Gameboy *gb);

  LCDController &get_lcd() {
    return lcd;
  }

  TileRenderer &get_tile_renderer() {
    return tile_renderer;
  }

  SpriteRenderer &get_sprite_renderer() {
    return sprite_renderer;
  }

  Framebuffer &get_framebuffer() {
    return framebuffer;
  }

  Gameboy *get_gameboy() {
    return gameboy;
  }

  Register8 get_lcd_lcdc() {
    return lcd.lcdc;
  }

  Register8 get_lcd_stat() {
    return lcd.stat;
  }

  Register8 get_lcd_ly() {
    return lcd.ly;
  }

  Register8 get_lcd_lyc() {
    return lcd.lyc;
  }

  Register8 get_tile_scy() {
    return tile_renderer.scy;
  }

  Register8 get_tile_scx() {
    return tile_renderer.scx;
  }

  Register8 get_tile_wy() {
    return tile_renderer.wy;
  }

  Register8 get_tile_wx() {
    return tile_renderer.wx;
  }

  Register8 get_tile_bgp() {
    return tile_renderer.bgp;
  }

  Register8 get_sprite_obp0() {
    return sprite_renderer.obp0;
  }

  Register8 get_sprite_obp1() {
    return sprite_renderer.obp1;
  }
};