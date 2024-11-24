#pragma once

class CPU {
    private:
        u16 af;
    public:
        CPU();

        void init();
        bool step();
};
