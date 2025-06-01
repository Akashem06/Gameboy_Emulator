#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

const u32 GAMEBOY_WIDTH = 160U;
const u32 GAMEBOY_HEIGHT = 144U;
const u32 BG_MAP_SIZE = 256U;

const u32 CLOCK_RATE = 4194304U;

void delay_ms(u32 ms);
