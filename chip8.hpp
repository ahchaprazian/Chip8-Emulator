#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <stdint.h>
#include <stack>
#include <vector>
#include <string>

#include "/opt/homebrew/include/SDL2/SDL.h"

class Chip8 {
public:
    Chip8();
    ~Chip8();

    uint8_t getKeypad(int index) const;
    
    void loadROM(const std::string& romFile);
    uint16_t fetch();
    void decode();
    void execute();

private:
    uint16_t mem[4096];            // 4kilo memory
    uint16_t v[16];                // v registers v0-vf
    uint16_t i;                    // index register
    int pc;                        // program counter

    std::stack<uint16_t> stack;    // stack
    int sp;                        // stack pointer

    uint8_t delayTimer;
    uint8_t soundTimer;

    std::vector<uint8_t> font;
    std::vector<uint8_t> keypad;

};

#endif