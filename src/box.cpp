#include "box.h"

int Box::size()
{
    return _size;
}

void Box::move(int x_shift, int y_shift)
{
    _xPos += x_shift;
    _yPos += y_shift;
}

void Box::add_to_render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {_xPos, _yPos, _size, _size};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 250);
    SDL_RenderFillRect(renderer, &rect);
}
