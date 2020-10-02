#include <SDL2/SDL.h>

#ifndef _Box_H
#define _Box_H

class Box
{
public:
    Box(int x_pos, int y_pos) : _xPos{x_pos}, _yPos{y_pos} {};
    void add_to_render(SDL_Renderer* renderer);
    void move(int x_shift, int y_shift);
    int size();
private:
    int _xPos = 0;
    int _yPos = 0;

    const int _size = 10;
};

#endif // Box
