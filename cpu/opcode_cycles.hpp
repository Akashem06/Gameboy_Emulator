#pragma once

#include "common.hpp"

const u8 opcode_cycles[256U] = { 1U, 3U, 2U, 2U, 1U, 1U, 2U, 1U, 5U, 2U, 2U, 2U, 1U, 1U, 2U, 1U, 1U, 3U, 2U, 2U, 1U, 1U, 2U, 1U, 3U, 2U, 2U, 2U, 1U,
                                 1U, 2U, 1U, 2U, 3U, 2U, 2U, 1U, 1U, 2U, 1U, 2U, 2U, 2U, 2U, 1U, 1U, 2U, 1U, 2U, 3U, 2U, 2U, 3U, 3U, 3U, 1U, 2U, 2U,
                                 2U, 2U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U,
                                 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 2U, 2U, 2U, 2U,
                                 2U, 2U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U,
                                 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
                                 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 2U, 3U, 3U, 4U, 3U, 4U, 2U, 4U, 2U, 4U, 3U,
                                 0U, 3U, 6U, 2U, 4U, 2U, 3U, 3U, 0U, 3U, 4U, 2U, 4U, 2U, 4U, 3U, 0U, 3U, 0U, 2U, 4U, 3U, 3U, 2U, 0U, 0U, 4U, 2U, 4U,
                                 4U, 1U, 4U, 0U, 0U, 0U, 2U, 4U, 3U, 3U, 2U, 1U, 0U, 4U, 2U, 4U, 3U, 2U, 4U, 1U, 0U, 0U, 2U, 4U };

const u8 opcode_cycles_branched[256U] = {
  1U, 3U, 2U, 2U, 1U, 1U, 2U, 1U, 5U, 2U, 2U, 2U, 1U, 1U, 2U, 1U, 1U, 3U, 2U, 2U, 1U, 1U, 2U, 1U, 3U, 2U, 2U, 2U, 1U, 1U, 2U, 1U, 3U, 3U, 2U, 2U, 1U,
  1U, 2U, 1U, 3U, 2U, 2U, 2U, 1U, 1U, 2U, 1U, 3U, 3U, 2U, 2U, 3U, 3U, 3U, 1U, 3U, 2U, 2U, 2U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U,
  1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U,
  1U, 2U, 2U, 2U, 2U, 2U, 2U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U,
  1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 1U, 1U,
  1U, 1U, 1U, 1U, 1U, 2U, 1U, 5U, 3U, 4U, 4U, 6U, 4U, 2U, 4U, 5U, 4U, 4U, 0U, 6U, 6U, 2U, 4U, 5U, 3U, 4U, 0U, 6U, 4U, 2U, 4U, 5U, 4U, 4U, 0U, 6U, 0U,
  2U, 4U, 3U, 3U, 2U, 0U, 0U, 4U, 2U, 4U, 4U, 1U, 4U, 0U, 0U, 0U, 2U, 4U, 3U, 3U, 2U, 1U, 0U, 4U, 2U, 4U, 3U, 2U, 4U, 1U, 0U, 0U, 2U, 4U
};

const u8 opcode_cycles_cb[256U] = {
  2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U,
  2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U,
  2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U,
  2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 3U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U,
  2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U,
  2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U,
  4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 4U, 2U
};
