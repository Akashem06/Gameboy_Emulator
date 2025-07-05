#include "serial.hpp"
#include "gameboy.hpp"
#include <iostream>

Serial::Serial() : sb_register(0x00), sc_register(0x00), gameboy(nullptr) {
}

u8 Serial::read() {
    return sb_register;
}

u8 Serial::read_control() {
    return sc_register;
}

void Serial::write(u8 byte) {
    sb_register = byte;
}

void Serial::write_control(u8 byte) {
    sc_register = byte;

    if ((sc_register & 0x81U) == 0x81U) {
        char received_char = static_cast<char>(sb_register);
        std::cout << received_char;
        sc_register &= ~0x81U;
    }
}

void Serial::set_gameboy(Gameboy *gb) {
    this->gameboy = gb;
}
