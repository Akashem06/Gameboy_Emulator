#pragma once

#include "common.hpp"

using Address = u16;

#define MEMORY_IN_RANGE(address, lower, upper) (address >= lower && address <= upper? true : false)
