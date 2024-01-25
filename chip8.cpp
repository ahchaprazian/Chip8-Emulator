#include <iostream>
#include <fstream>
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
        this->memory[i] = 0;
    }

    for(unsigned int i = 0; i < FONTSET_SIZE; i++) {
        this->memory[FONTSET_START_ADDRESS + i] = font[i];
    }

    for(int i = 0; i < 16; i++) {
        this->registers[i] = 0;
        this->stack[i] = 0;
        this->keypad[i] = 0;
    }

    for(int i = 0; i < (64 * 32); i++) {
        this->video[i] = 0;
    }

    this->randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

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
        this->memory[START_ADDRESS + i] = buffer[i];
    }

    delete[] buffer;


    BOOST_LOG_TRIVIAL(info) << "ROM has successfully loaded.";
    return true;
}

uint32_t Chip8::get_graphic(int i) {
    return video[i];
}

void Chip8::set_key(int i, int keyPressedEvent) {

}

void Chip8::decodeAndExecute() {

    opcode = (memory[programCounter] << 8) | memory[programCounter + 1];

    uint8_t instructionType = (opcode & 0xF000) >> 12; // 0xN000 -< 1st nibble which is the instruction type
    uint8_t registerVX = (opcode & 0x0F00) >> 8;      // 0x0X00 <- 2nd nibble one of 16 registers from V0-VF
    uint8_t registerVY = (opcode & 0x00F0) >> 4;      // 0x00Y0 <- 3rd nibble one of 16 registers from V0-VF
    uint8_t N = opcode & 0x000F;               // 0x000N <- 4 bit number (4th nibble)
    uint8_t NN = opcode & 0x00FF;              // 0x00NN <- 8 bit immidate number (3rd and 4th nibbles)
    uint16_t NNN = opcode & 0x0FFF;            // 0x0NNN <- 12 bit immediate memory address (2nd, 3rd, and 4th nibbles)

    unsigned short x;
    unsigned short y;
    unsigned short height;

    switch(instructionType) {
        case 0x0:
            if(opcode == 0x00E0) {
                memset(video, 0, sizeof(video));
                programCounter += 2;
                BOOST_LOG_TRIVIAL(info) << "Screen Cleared";
            }
            if(opcode == 0X00EE) {
                stackPointer--;
                programCounter = stack[stackPointer];
                programCounter += 2;
            }
            break;
        case 0x1:
            programCounter = NNN;
            BOOST_LOG_TRIVIAL(info) << "Jumped to address NNN";
            break;
        case 0x2:
            stack[stackPointer] = programCounter;
            stackPointer++;
            programCounter = NNN;
            break;
        case 0x3:
            if(registers[registerVX] == NN) {
                programCounter += 2;
            }
            programCounter += 2;
            break;
        case 0x4:
            if(registers[registerVX] != NN) {
                programCounter +=2;
            }
            programCounter += 2;
            break;
        case 0x5:
            if(registers[registerVX] == registers[registerVY]) {
                programCounter += 2;
            }
            programCounter += 2;
            break;
        case 0x6:
            registers[registerVX] = NN;
            programCounter += 2;
            BOOST_LOG_TRIVIAL(info) << "Set VX = NN";
            break;
        case 0x7:
            registers[registerVX] += NN;
            programCounter += 2;
            BOOST_LOG_TRIVIAL(info) << "Added NN to VX";
            break;
        case 0x8:
            if(N == 0x0000) {
                registers[registerVX] = registers[registerVY];
                programCounter += 2;
            }
            if(N == 0x0001) {
                registers[registerVX] = registers[registerVX] | registers[registerVY];
                programCounter += 2;
            }
            if(N == 0x0002) {
                registers[registerVX] = registers[registerVX] & registers[registerVY];
                programCounter += 2;
            }
            if(N == 0x0003) {
                registers[registerVX] = registers[registerVX] ^ registers[registerVY];
                programCounter += 2;
            }
            if(N == 0x0004) {
                registers[registerVX] += registers[registerVY];

                uint8_t overflow = 0xFF - registers[registerVX];

                if(registers[registerVY] > overflow) {
                    registers[0xF] = 1;
                } else {
                    registers[0xF] = 0;
                }
                programCounter += 2;
            }
            if(N == 0x0005) {
                if(registers[registerVX] > registers[registerVY]) {
                    registers[0xF] = 1;
                } else {
                    registers[0xF] = 0;
                }
                registers[registerVX] -= registers[registerVY];
                programCounter += 2;
            }
            if(N == 0x0006) {
                registers[registerVX] = registers[registerVY];
                bool bit = registers[registerVX] & 1;
                registers[registerVX] >>= 1;

                if(bit) {
                    registers[0xF] = 1;
                } else {
                    registers[0xF] = 0;
                }
                programCounter += 2;
            }
            if(N == 0x0007) {
                if(registers[registerVX] < registers[registerVY]) {
                    registers[0xF] = 1;
                } else {
                    registers[0xF] = 0;
                }
                registers[registerVX] = registers[registerVY] - registers[registerVX];
                programCounter += 2;
            }
            if(N == 0x000E) {
                registers[0xF] = registers[registerVX] >> 7;
                registers[registerVX] <<= 1;
                programCounter += 2;
            }
            break;
        case 0x9:
            if(registers[registerVX] != registers[registerVY]) {
                programCounter += 2;
            }
            programCounter += 2;
            break;
        case 0xA:
            index = NNN;
            programCounter += 2;
            break;
        case 0xB:
            programCounter = NNN + registers[0];
            break;
        case 0xC:
            registers[registerVX] = randByte(randGen) & NN;
            programCounter += 2;
            break;
        case 0xD:
            unsigned short pixel;
            x = registers[registerVX] % 64;
            y = registers[registerVY] % 32;
            height = N;

            registers[0xF] = 0;
            for(int yAxis = 0; yAxis < height; yAxis++){
                pixel = memory[index + yAxis];
                for (int xAxis = 0; xAxis < 8; xAxis++) {
                    if((pixel & (0x80 >> xAxis)) != 0) {
                        if(video[(x + xAxis + ((y + yAxis) *64))] == 1) {
                            video[0xF] = 1;
                        }
                        video[x+xAxis + ((y + yAxis) * 64)] ^= 1;
                    }
                }
            }
            programCounter += 2;
            BOOST_LOG_TRIVIAL(info) << "Coordinates Drawn";
            break;
        case 0xE:
            if(NN == 0x009E) {
                if (keypad[registers[registerVX]] != 0) {
                    programCounter += 2;
                } 
                programCounter += 2;
            }
            if(NN == 0x00A1) {
                if (keypad[registers[registerVX]] == 0) {
                    programCounter += 2;
                }
                programCounter += 2;
            }
            break;
        case 0xF:
            BOOST_LOG_TRIVIAL(info) << "Entered 0xF";
            if(N == 0x0007) {
                registers[registerVX] = delayTimer;
                programCounter += 2;
            }
            if(NN == 0x0015) {
                delayTimer = registers[registerVX];
                programCounter += 2;
            }
            if(NN == 0x0018) {
                soundTimer = registers[registerVX];
                programCounter += 2;
            }
            if(NN == 0x001E) {
                index += registers[registerVX];
                programCounter += 2;
            }
            if(NN == 0x000A) {
                bool isPressed = false;

                for (int i = 0; i < 16; i++) {
                    if(keypad[i] != 0) {
                        registers[registerVX] = i;
                        isPressed = true;
                    }
                }

                if(!isPressed) {
                    return;
                }

                programCounter += 2;
            }
            if(NN == 0x0029) {
                index = registers[registerVX] * 0x5;
                programCounter += 2;
            }
            if(NN == 0x0033) {
                memory[index] = (registers[registerVX] / 100);
                memory[index + 1] = ((registers[registerVX] / 10) % 10);
                memory[index + 2] = ((registers[registerVX]  % 100) % 10);
                programCounter += 2;
            }
            if(NN == 0x0055) {
                BOOST_LOG_TRIVIAL(info) << "Entered opcode FX55";
                for (uint8_t i = 0; i <= registerVX; ++i) {
                    memory[index + i] = registers[i];
                }
                BOOST_LOG_TRIVIAL(info) << "Completed FX55";
                index += registerVX + 1;
                //index = (uint16_t) index;
                programCounter += 2;
            }
            if(NN == 0x0065) {
                for (uint8_t i = 0; i <= registerVX; i++) {
                    registers[i] = memory[index + i];
                }
                index += registerVX + 1;
                //index = (uint16_t) index;
                programCounter += 2;
            }
            break;
        default:
            break;
    }
}

