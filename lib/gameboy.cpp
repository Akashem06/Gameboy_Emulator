#include <stdbool.h>
#include <cstdio>

#include "common.hpp"
#include "sdl_ui.hpp"
#include "gameboy.hpp"
#include "cartridge.hpp"
#include "cpu.hpp"

Gameboy::Gameboy() {
    paused = false;
    running = false;
    ticks = 0U;
}

int Gameboy::run(int argc, char **argv) {
    if (argv == nullptr) {
        return -1;
    }

    if (argc < 2) {
        printf("ERROR: Did not receive ROM file name\n");
        return -2;
    }

    Cartridge cartridge = Cartridge();
    CPU cpu = CPU();

    printf("%s", argv[1]);

    if (!cartridge.readInfo(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -3;
    }
    printf("Cart loaded..\n");

    SDLUI ui = SDLUI();

    cpu.init();

    running = true;
    paused = false;
    ticks = 0;

    while (running) {
        if (paused) {
            delay_ms(10);
            continue;
        }

        if (!cpu.step()) {
            printf("CPU Stopped\n");
            return -4;
        }

        ticks++;
    }

    return 0;
}

void Gameboy::reset() {
    paused = false;
    running = false;
    ticks = 0U;
}

bool Gameboy::isPaused() const {
    return paused;
}

bool Gameboy::isRunning() const {
    return running;
}

u64 Gameboy::getTicks() const {
    return ticks;
}

void Gameboy::pause() {
    paused = true;
}

void Gameboy::abort() {
    running = false;
}
