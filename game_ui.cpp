#include <SDL2/SDL.h>
#include "game_ui.h"

GameUI::~GameUI()
{
    SDL_DestroyRenderer(_mainRenderer);
    SDL_DestroyWindow(_mainWindow);
    SDL_Quit();
}

SDL_Renderer* GameUI::get_renderer()
{
    return _mainRenderer;
}

void GameUI::clear_render()
{
    SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 100);
    SDL_RenderClear(_mainRenderer);
}

void GameUI::render()
{
    SDL_RenderPresent(_mainRenderer);
}

