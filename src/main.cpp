#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

#include "box.h"
#include "game_ui.h"
#include "grid.h"
#include "arg_parser.h"


int main(int argc, char** argv)
{
    ArgParser parser;
    auto args = parser.parse(argc, argv);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, args.grid_size * 10, args.grid_size * 10,
            SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    Grid g(args.grid_size);
    g.sample_init_population(args.alive_percent);

    GameUI ui(window, renderer);
    auto start = std::chrono::steady_clock::now();
    bool quit = false;

    while (!quit && SDL_WaitEvent(&event))
    {
        quit = std::chrono::steady_clock::now() - start > std::chrono::seconds(args.timeout_seconds);

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

        std::this_thread::sleep_for(std::chrono::milliseconds(args.refresh_milliseconds));
    }
}
