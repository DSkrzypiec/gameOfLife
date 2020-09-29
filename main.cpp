#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

constexpr int SCREEN_HEIGHT = 480;
constexpr int SCREEN_WIDTH = 620;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    auto window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    SDL_Rect rect = {200, 200, 100, 50};
    auto start = std::chrono::steady_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = std::chrono::steady_clock::now() - start > std::chrono::seconds(15);

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        rect.x += 3;
        rect.y += 1;

        if (rect.x > 620) {
            rect.x = 0;
        }
        if (rect.y > 480) {
            rect.y = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 120, 100, 50, 200);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
