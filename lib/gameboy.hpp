#pragma once

#include <stdbool.h>

#include "common.hpp"

class Gameboy {
    private:
        bool paused;
        bool running;
        u64 ticks;
    public:
        Gameboy();

        int run(int argc, char **argv);

        void reset();

        bool isPaused() const;
        bool isRunning() const;
        u64 getTicks() const;

        void pause();
        void abort();
};
