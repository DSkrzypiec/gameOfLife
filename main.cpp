#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

#include "box.h"
#include "game_ui.h"


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 620, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    GameUI ui(window, renderer);
    Box box(50, 250);
    Box box2(100, 400);
    auto start = std::chrono::steady_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = std::chrono::steady_clock::now() - start > std::chrono::seconds(15);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        ui.clear_render();

        box.move(4, 1);
        box2.move(1, -1);

        box.add_to_render(ui.get_renderer());
        box2.add_to_render(ui.get_renderer());

        ui.render();
    }

    return 0;
}
