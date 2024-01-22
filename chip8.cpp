#include <iostream>
#include <fstream>
#include <random>
#include "chip8.hpp"


const unsigned int START_ADDRESS = 0x200;

const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0X50;

uint8_t font[FONTSET_SIZE] = {
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


Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{ 
    // init program counter
    this->pc = START_ADDRESS;

    for(unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = font[i];
    }

    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

bool Chip8::loadROM(const std::string& romFilename){
    std::ifstream romFile(romFilename, std::ios::binary | std::ios::ate);

    if(!romFile.is_open()){
        return false;
    }

    std::streampos size = romFile.tellg();
    char* buffer = new char[size];

    romFile.seekg(0, std::ios::beg);
    romFile.read(buffer, size);
    romFile.close();

    for(long i = 0; i < size; i++){
        memory[START_ADDRESS + i] = buffer[i];
    }

    delete[] buffer;
}

