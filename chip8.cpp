#include <iostream>
#include "chip8.hpp"

Chip8::Chip8() { 
    this->pc          = 0x200;
    this->i           = 0;
    this->sp          = 0;
    this->delayTimer  = 0;
    this->soundTimer  = 0;

    font = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    keypad = {
        SDLK_1, SDLK_2, SDLK_3, SDLK_4,
        SDLK_q, SDLK_w, SDLK_e, SDLK_r,
        SDLK_a, SDLK_s, SDLK_d, SDLK_f,
        SDLK_z, SDLK_x, SDLK_c, SDLK_v
    };

    for (int i = 0; i < 16; i++) {
        this->v[i] = 0;
    }

    for (int i = 0; i < 4096; i++) {
        this->mem[i] = 0;
    }

    for (int i = 0; i < 80; i++) {
        this->mem[i] = font[i];
    }
}

Chip8::~Chip8() {}

uint8_t Chip8::getKeypad(int index) const {
    return this->keypad.at(index);
}

void Chip8::loadROM(const std::string& romFile){
    std::cout << "ROM STUB BOYO\n";
}

uint16_t Chip8::fetch() {
    uint16_t opcode = this->mem[pc] << 8 | this->mem[pc + 1];
    this->pc += 2;

    return opcode;
}
void Chip8::decode() {
    std::cout << "DECODE STUB BOYO\n";
}
void Chip8::execute() {
    std::cout << "EXECUTE STUB LADDY\n";
}