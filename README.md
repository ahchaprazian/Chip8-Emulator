# CHIP8 Emulator

## Project Details
This C++ project is a CHIP-8 emulator designed to recreate the vintage computing environment of the 1970s. CHIP-8 is an interpreted programming language used for early microcomputers. The emulator's goal is to accurately simulate the CHIP-8 system, including its processor, memory, input handling, display, and timers. Key components involve initializing memory, loading programs, implementing the main emulation loop, graphics rendering, input mapping, and timers. The project offers a valuable learning experience in low-level programming, system architecture, and emulation.

## Required Libraries
- Simple DirectMedia Layer (SDL) for graphics and input handling.
  Install SDL using the package manager or download from [SDL Official Website](https://www.libsdl.org/download-2.0.php)
- (Not required) Boost for using the loggers for debugging purposes

## How to Run
1. Clone the repository: `https://github.com/ahchaprazian/Chip8-Emulator`
2. Navigate to the project directory: `cd Chip8-Emulator`
3. Build the emulator using the Makefile: `make`
4. Download any chip8 rom that you may want to play make sure rom ends in `.ch8`
4. Run the emulator: `./chip8 roms/romName.ch8`
    - note replace romName with the name of whatever chip8 rom you would like to use

## Learning Objectives
1. Understanding Chip-8 Architecture:
    - Learned about the Chip-8 architecture, including its memory structure, registers, and instruction set.
    - Explored the purpose and functionality of each component in the Chip-8 system.

2. Assembly Language Programming:
    - Gained proficiency in Chip-8 assembly language to understand how programs are written for the platform.
    - Wrote C++ implementation of each instruction needed to build a Chip-8 rom

3. Memory Management:
    - Found out how memory is organized in the Chip-8 system, including the stack, program counter, and other memory regions.

4. Display and Graphics:
    - Learned how the Chip-8 handles graphics and display output.
    - Implemented graphics rendering routines to draw pixels on the screen according to Chip-8 opcode instructions.

5. Input Handling:
    - Noted the input system of Chip-8, which typically involves a hexadecimal keypad.
    - Implemented input handling routines to process key presses and update the state of the input registers.

6. Emulation Loop:
    - Applied the main emulation loop that fetches, decodes, and executes Chip-8 instructions.
    - Understand the timing aspects of emulation to ensure accurate execution of programs.

8. Testing and Debugging:
    - Developed strategies for testing the emulator, including boost loggers to view how each instruction was being accessed and if there was any blockages