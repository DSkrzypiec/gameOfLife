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

    Grid g(80);
    g.sample_init_population(0.10);

    GameUI ui(window, renderer);
    auto start = std::chrono::steady_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = std::chrono::steady_clock::now() - start > std::chrono::seconds(60);

        ui.clear_render();
        g.render(ui.get_renderer());
        //g.print_raw();
        ui.render();
        g.next_generation();

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        //std::this_thread::sleep_for(std::chrono::seconds(12));
    }

    return 0;
}
