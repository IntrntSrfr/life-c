#ifndef GRID_
#define GRID_

#include <stdbool.h>

typedef struct {
  bool *data;
  int height;
  int width;
  bool wrap;
} Grid;

Grid *new_grid(int height, int width, bool wrap);
void destroy_grid(Grid *grid);
void copy_grid(const Grid *src, Grid *dst);
void randomize_grid(Grid *grid, float p);
void step_grid(const Grid *grid, Grid *dst);
void get_wrapped_grid_pos(const Grid *grid, int *x, int *y);
bool at_grid_pos(const Grid *grid, int x, int y);
void set_grid_pos(Grid *grid, int x, int y, bool value);
int grid_pos_neighbours(const Grid *grid, int x, int y);
void print_grid(const Grid *grid);

#endif