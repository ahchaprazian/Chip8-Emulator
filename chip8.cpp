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

void Chip8::decodeAndExecute(uint16_t opcode) {
    //decode first four bits to get opcode type
    uint16_t opType = (opcode & 0xF000) >> 12;

    switch(opType) {
        case 0x0:
            // TODO codes 00E0, 00EE, 0nnn
            break;
        case 0x1:
            // TODO 1nnn
            break;
        case 0x2:
            // TODO 2nnn
            break;
        case 0x3:
            // TODO 3xkk
            break;
        case 0x4:
            // TODO 4xkk
            break;
        case 0x5:
            // TODO 5xy0
            break;
        case 0x6:
            // TODO 6xkk
            break;
        case 0x7:
            // TODO 7xkk
            break;
        case 0x8:
            // TODO 8xy0, 8xy1, 8xy2, 8xy3, 8xy4, 8xy5, 8xy6, 8xy7, 8xyE
            break;
        case 0x9:
            // TODO 9xy0
            break;
        case 0xA:
            // TODO Annn
            break;
        case 0xB:
            // TODO Bnnn
            break;
        case 0xC:
            // TODO Cxkk
            break;
        case 0xD:
            // TODO Dxyn
            break;
        case 0xE:
            // TODO Ex9E, ExA1
            break;
        case 0xF:
            // TODO Fx07, Fx0A, Fx15, Fx18, Fx1E, Fx29, Fx33, Fx55, Fx65
            break;

        default:
            break;
    }
}