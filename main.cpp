#include <iostream>

//#include "/opt/homebrew/include/SDL2/SDL.h"
#include "chip8.hpp"


int main(int argc, char* argv[]) {

    if(argv[1] == NULL) {   // check if a rom was insterted if not print error and exit
        fprintf(stderr, "ERROR: No rom was insterted\n");
        exit(1);
    }

    Chip8 chip8Emulator = Chip8();
    chip8Emulator.loadROM(argv[1]);
    uint16_t opcode = chip8Emulator.fetch();
    chip8Emulator.decodeAndExecute(opcode);
    

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Chip-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024, 640,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // if (renderer == nullptr) {
    //     SDL_Log("Failed to create renderer: %s", SDL_GetError());
    //     return 1;
    // }

    // bool quit = false;
    // SDL_Event event;

    // int colorIndex = 0;
    // const SDL_Color colors[] = {
    //     {255, 0, 0, 255},   // Red
    //     {0, 255, 0, 255},   // Green
    //     {0, 0, 255, 255},   // Blue
    //     {255, 255, 0, 255}, // Yellow
    // };

    // while (!quit) {
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             quit = true;
    //         }
    //     }

    //     // Clear the renderer with the current color
    //     SDL_SetRenderDrawColor(renderer, colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, colors[colorIndex].a);
    //     SDL_RenderClear(renderer);
    //     SDL_RenderPresent(renderer);

    //     // Cycle through colors
    //     colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));

    //     // Add a short delay
    //     SDL_Delay(1000);
    // }

    // Clean up and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
