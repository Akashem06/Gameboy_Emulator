#!/bin/bash

set -o errexit
set -o nounset

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
RESET="\e[0m"

BUILD_DIR="build"

echo -e "${BLUE}--- Setting up and Running Blargg Tests ---${RESET}"

if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${YELLOW}Creating build directory: ${BUILD_DIR}${RESET}"
    mkdir -p "$BUILD_DIR"
fi

echo -e "${YELLOW}Navigating to build directory: ${BUILD_DIR}${RESET}"
cd "$BUILD_DIR"

echo -e "${BLUE}Configuring CMake project...${RESET}"
cmake ..

echo -e "${BLUE}Building the project...${RESET}"
cmake --build .

if [ ! -f "gameboy_emulator" ]; then
    echo -e "${RED}Error: gameboy_emulator executable not found in ${BUILD_DIR}. Build failed.${RESET}"
    exit 1
fi

echo -e "${BLUE}Running Blargg tests with CTest...${RESET}"
if ctest --output-on-failure; then
    echo -e "${GREEN}All Blargg tests passed!${RESET}"
    exit 0
else
    echo -e "${RED}Some Blargg tests failed! Check the output above.${RESET}"
    exit 1
fi
