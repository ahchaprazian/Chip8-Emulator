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
    this->programCounter = START_ADDRESS;
    this->index = 0;
    this->delayTimer = 0;
    this->soundTimer = 0;
    this->opcode = 0;
    this->stackPointer = 0;

    for(unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[i] = 0;
    }

    for(unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = font[i];
    }

    for(int i = 0; i < 16; i++) {
        this->registers[i] = 0;
        this->stack[i] = 0;
        this->keypad[i] = 0;
    }

    for(int i = 0; i < (64 * 32); i++) {
        this->video[i] = 0;
    }

    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

    BOOST_LOG_TRIVIAL(info) << "Succesfully constructed Chip8 Object.";
}

bool Chip8::loadROM(const std::string& romFilename){
    std::ifstream romFile(romFilename, std::ios::binary | std::ios::ate);

    if(!romFile.is_open()){
        BOOST_LOG_TRIVIAL(error) << "Failed to load ROM.";
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


    BOOST_LOG_TRIVIAL(info) << "ROM has successfully loaded.";
    return true;
}

void Chip8::decodeAndExecute(uint16_t opcode) {

    uint8_t instructionType = (opcode & 0xF000) >> 12; // 0xN000 -< 1st nibble which is the instruction type
    uint8_t registerVX = (opcode & 0x0F00) >> 8;      // 0x0X00 <- 2nd nibble one of 16 registers from V0-VF
    uint8_t registerVY = (opcode & 0x00F0) >> 4;      // 0x00Y0 <- 3rd nibble one of 16 registers from V0-VF
    uint8_t N = opcode & 0x000F;               // 0x000N <- 4 bit number (4th nibble)
    uint8_t NN = opcode & 0x00FF;              // 0x00NN <- 8 bit immidate number (3rd and 4th nibbles)
    uint16_t NNN = opcode & 0x0FFF;            // 0x0NNN <- 12 bit immediate memory address (2nd, 3rd, and 4th nibbles)


    switch(instructionType) {
        case 0x0:
            break;
        case 0x1:
            break;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x4:
            break;
        case 0x5:
            break;
        case 0x6:
            break;
        case 0x7:
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            break;
        case 0xE:
            break;
        case 0xF:
            break;
        default:
            break;
    }
}

