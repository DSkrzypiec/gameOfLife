#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

#include "box.h"
#include "game_ui.h"
#include "grid.h"


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    Grid g(80);
    g.sample_init_population(0.60);

    GameUI ui(window, renderer);
    auto start = std::chrono::steady_clock::now();
    bool quit = false;

    while (!quit && SDL_WaitEvent(&event))
    {
        quit = std::chrono::steady_clock::now() - start > std::chrono::seconds(20);

        switch(event.type) {
            case SDL_QUIT:
                quit = true;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
        }

        ui.clear_render();
        g.render(ui.get_renderer());
        ui.render();
        g.next_generation();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
