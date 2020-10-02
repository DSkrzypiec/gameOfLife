#include <iostream>
#include <random>

#include "grid.h"
#include "box.h"


// Default constructor.
Grid::Grid()
{
    _grid_size = 100;
    _grid = create_grid();
}

// Grid size constructor.
Grid::Grid(int grid_size)
{
    _grid_size = grid_size;
    _grid = create_grid();
}

// Method sample_init_population for given percentage of alive cells samples
// alive cells on the grid. This method would be called usually at the
// beginning and after that cells would live according to Conway's rules.
void Grid::sample_init_population(double percent_of_alive)
{
    if (percent_of_alive < 0.0 || percent_of_alive >= 1.0) {
        throw "Given 'percent_of_alive' should be from interval [0, 1)";
    }

    int alive_number = percent_of_alive * _grid_size;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> index(0, _grid_size - 1);
    int idx = 0;

    for (auto i = 0; i < _grid_size; i++) {
        for (auto j = 0; j < alive_number; j++) {
            idx = index(mt);
            _grid[i][idx] = true;
        }
    }
}

// This method simulates the next generation. For each cell Conway's rules are
// applied and the state for the next generation is determined. Grid is
// updated.
void Grid::next_generation()
{
    auto next_gen_grid = create_grid();

    for (auto x_pos = 0; x_pos < _grid_size; x_pos++) {
        for (auto y_pos = 0; y_pos < _grid_size; y_pos++) {
            next_gen_grid[x_pos][y_pos] = state_in_next_gen(x_pos, y_pos);
        }
    }

    _grid = next_gen_grid;
}

// Method render renderes current version of the grid. Alive cells are
// preseneted as white squares (20x20px).
void Grid::render(SDL_Renderer* renderer)
{
    Box tmp(-1, -1);
    int x_pos = 0;
    int y_pos = 0;
    int step = tmp.size();

    for (auto rowId = 0; rowId < _grid_size; rowId++) {
        y_pos += step;
        x_pos = 0;

        for (auto colId = 0; colId < _grid_size; colId++) {
            x_pos += step;

            if (_grid[rowId][colId]) {
                Box box(x_pos, y_pos);
                box.add_to_render(renderer);
            }
        }
    }
}

// Private methods.

// Initialize the grid.
std::vector<std::vector<bool>> Grid::create_grid()
{
    std::vector<std::vector<bool>> grid;
    grid.reserve(_grid_size);

    for (auto i = 0; i < _grid_size; i++) {
        std::vector<bool> row;
        row.reserve(_grid_size);

        for (auto j = 0; j < _grid_size; j++) {
            row.push_back(false);
        }
        grid.push_back(row);
    }

    return grid;
}

// This method determines state of given cell in the next generation according
// to Conway's rules.
bool Grid::state_in_next_gen(int x_pos, int y_pos)
{
    if (is_outside_grid(x_pos, y_pos)) {
        return false;
    }

    int adj = neighbours(x_pos, y_pos);

    // alive in current gen
    if (_grid[x_pos][y_pos]) {
        return adj == 2 || adj == 3;
    }

    // dead in current gen
    return adj == 3;
}

// Returns number of neighbours - cells which interacts with (x_pos, y_pos)
// cell.
int Grid::neighbours(int x_pos, int y_pos)
{
    if (is_outside_grid(x_pos, y_pos)) {
        return 0;
    }

    int count = 0;
    auto neighbour_state = [=](int x_inc, int y_inc) {
        return (int)single_neighbour_state(x_pos, y_pos, x_inc, y_inc);
    };

    for (auto x_inc : {-1, 0, 1}) {
        for (auto y_inc : {-1, 0, 1}) {
            if (x_inc == 0 && y_inc == 0) {
                continue; // cell itself
            }

            count += neighbour_state(x_inc, y_inc);
        }
    }

    return count;
}

// Checks state of neighbour (shifted by (x_inc, y_inc) of cell (x_pos, y_pos).
// State fasle == dead, true == alive.
bool Grid::single_neighbour_state(int x_pos, int y_pos, int x_inc, int y_inc)
{
    int x_n = x_pos + x_inc;
    int y_n = y_pos + y_inc;

    if (is_outside_grid(x_n, y_n)) {
        return false;
    }

    return _grid[x_n][y_n];
}

// Checks if given coordinates are outside of the grid.
bool Grid::is_outside_grid(int x_pos, int y_pos)
{
    if (x_pos < 0 || x_pos >= _grid_size) {
        return true;
    }
    if (y_pos < 0 || y_pos >= _grid_size) {
        return true;
    }

    return false;
}

void Grid::print_raw()
{
    std::cout << " ------------------------------------------ " << std::endl;
    for (auto v : _grid) {
        for (auto e : v) {
            std::cout << e << "  ";
        }
        std::cout << std::endl;
    }
}
