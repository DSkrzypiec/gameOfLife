#ifndef _GRID_H
#define _GRID_H

#include <vector>
#include <SDL2/SDL.h>

class Grid
{
public:
    Grid();
    Grid(int grid_size);
    void sample_init_population(double precent_of_alive);
    void next_generation();
    void render(SDL_Renderer* renderer);
    void print_raw();

private:
    std::vector<std::vector<bool>> create_grid();
    bool state_in_next_gen(int x_pos, int y_pos);
    int neighbours(int x_pos, int y_pos);
    bool single_neighbour_state(int x_pos, int y_pos, int x_inc, int y_inc);
    bool is_outside_grid(int x_pos, int y_pos);


    int _grid_size;
    std::vector<std::vector<bool>> _grid;
};

#endif // _GRID_H
