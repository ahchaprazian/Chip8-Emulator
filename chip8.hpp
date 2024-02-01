#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <stdint.h>
#include <chrono>
#include <random>
#include <SDL2/SDL.h>
//#include <boost/log/trivial.hpp>

class Chip8 {
public:
    Chip8();

    void set_key(int i, int keyPressedEvent);
    
    bool loadROM(const std::string& romFilename);

    uint32_t get_graphic(int i);
    bool getDraw();
    void setDraw(bool draw);
    
    //uint16_t fetch();
    void decodeAndExecute();
    //void execute();

   
    

private:
    uint8_t registers[16] {};   // V register V0-VF
    uint8_t memory[4096] {};
    uint16_t index{};           // Index register
    uint16_t programCounter {};             // program counter
    uint16_t stack[16] {};      // Stack
    uint8_t stackPointer{};               // stack pointer
    uint8_t delayTimer {};
    uint8_t soundTimer {};
    uint8_t keypad[16] {};      
    uint32_t video[64 * 32] {}; // graphics
    uint16_t opcode;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

    bool draw;
};  

#endif