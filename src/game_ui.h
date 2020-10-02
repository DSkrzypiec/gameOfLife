#include <SDL2/SDL.h>

#ifndef _GAME_UI_H
#define _GAME_UI_H

class GameUI
{
public:
    GameUI(SDL_Window* window, SDL_Renderer* renderer)
        : _mainWindow{window}, _mainRenderer{renderer} {};
    ~GameUI();

    SDL_Renderer* get_renderer();
    void clear_render();
    void render();

private:
    SDL_Window* _mainWindow;
    SDL_Renderer* _mainRenderer;
};

#endif // _GAME_UI_H
