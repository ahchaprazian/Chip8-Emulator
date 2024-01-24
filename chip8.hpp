#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <stdint.h>
#include <stack>
#include <string>
#include <chrono>
#include <random>

#include <SDL2/SDL.h>
#include <boost/log/trivial.hpp>

class Chip8 {
public:
    Chip8();
    
    bool loadROM(const std::string& romFilename);
    
    //uint16_t fetch();
    void decodeAndExecute(uint16_t opcode);
    //void execute();

private:
    uint8_t registers[16] {};
    uint8_t memory[4096] {};
    uint16_t index{};
    uint16_t pc {};             // program counter
    uint16_t stack[16] {};
    uint8_t sp{};               // stack pointer
    uint8_t delayTimer {};
    uint8_t soundTimer {};
    uint8_t keypad[16] {};
    uint32_t video[64 * 32] {};
    uint16_t opcode;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;
};  

#endif