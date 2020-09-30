#include "box.h"

void Box::move(int x_shift, int y_shift)
{
    _xPos += x_shift;
    _yPos += y_shift;

    if (_xPos > _maxX) {
        _xPos = 0;
    }

    if (_yPos > _maxY) {
        _yPos = 0;
    }
}

void Box::add_to_render(SDL_Renderer* renderer)
{
    SDL_Rect frame = {_xPos, _yPos, _size, _size};
    SDL_Rect inner = {_xPos + _delta, _yPos + _delta,
        _size - 2*_delta, _size - 2*_delta};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 250);
    SDL_RenderFillRect(renderer, &frame);

    SDL_SetRenderDrawColor(renderer, 140, 155, 255, 250);
    SDL_RenderFillRect(renderer, &inner);
}
