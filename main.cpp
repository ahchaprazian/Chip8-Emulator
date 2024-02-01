#include <iostream>

//#include <boost/log/trivial.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <chrono>
#include <thread>
#include "chip8.hpp"


uint8_t keyboard[16] = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3,
    SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c,
    SDLK_4, SDLK_r, SDLK_f, SDLK_v
};

int main(int argc, char* argv[]) {

    if(argv[1] == NULL) {   // check if a rom was insterted if not print error and exit
        std::cerr << "ERROR: ROM file was not inserted.\n";
        //BOOST_LOG_TRIVIAL(error) << "No ROM file was inserted.";
        std::exit(EXIT_FAILURE);
    }

    //BOOST_LOG_TRIVIAL(info) << "Correct number of arguments passed in.";

    Chip8 chip8Emulator = Chip8();

    if(!chip8Emulator.loadROM(argv[1])) {
        std::cerr << "ERROR: ROM failed to load.\n";
        std::exit(EXIT_FAILURE);
    }


    //uint16_t opcode = chip8Emulator.fetch();
    //chip8Emulator.decodeAndExecute(opcode);
    


    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    const int height = 520, width = 1080;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        //return 1;
        std::cerr << "ERROR: failed to initialize SDL " << SDL_GetError() << "\n";
        SDL_Quit();
        std::exit(EXIT_FAILURE);
    }

    // Create a window
    window = SDL_CreateWindow(
        "Chip-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        std::cerr << "ERROR: failed to create window " << SDL_GetError() << "\n";
        std::exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Failed to init rendering: %s", SDL_GetError());
        std::cerr << "ERROR: failed to init rendering " << SDL_GetError() << "\n";
        std::exit(EXIT_FAILURE);
    }

    SDL_RenderSetLogicalSize(renderer, width, height);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    if (texture == nullptr) {
        SDL_Log("Failed to init texture: %s", SDL_GetError());
        std::cerr << "ERROR: failed to init texture " << SDL_GetError() << "\n";
        std::exit(EXIT_FAILURE);
    }

    SDL_Event event;
    bool quit = false;
    uint32_t pixels[2048];
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }

            if(event.type == SDL_KEYDOWN){
                for(int i = 0; i < 16; i++) {
                    if(event.key.keysym.sym == keyboard[i]) {
                        chip8Emulator.set_key(i, 1);
                        //std::cout << "SDL Keycode: " << event.key.keysym.sym << std::endl;

                        //std::cout << "Key pressed: " << i << std::endl;
                    }
                }
            } 
            if(event.type == SDL_KEYUP) {
                for(int i = 0; i < 16; i++) {
                    if(event.key.keysym.sym == keyboard[i]) {
                        chip8Emulator.set_key(i, 0);
                        //std::cout << "Key pressed: " << i << std::endl;
                    }
                }
            }
        }

        chip8Emulator.decodeAndExecute();
        //chip8Emulator.getDraw();
        if (chip8Emulator.getDraw()) {
            chip8Emulator.setDraw(false);
            for(int i = 0; i < 2048; i++) {
                uint32_t pixel = chip8Emulator.get_graphic(i);
                pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
            }

            SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(Uint32));

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1200));
        //SDL_Delay(10);
    }

    // Clean up and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
