#include "grid.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Grid *new_grid(int height, int width, bool wrap) {
  Grid *grid = malloc(sizeof(Grid));
  if (!grid) return NULL;
  grid->height = height;
  grid->width = width;
  grid->wrap = wrap;
  grid->data = calloc(height * width, sizeof(bool));
  ;
  return grid;
}

void destroy_grid(Grid *grid) {
  free(grid->data);
  free(grid);
}

void randomize_grid(Grid *grid, float p) {
  if (!grid) return;
  srand(time(0));
  for (size_t y = 0; y < grid->height; y++)
    for (size_t x = 0; x < grid->width; x++)
      grid->data[y * grid->width + x] = (rand() % 2) == 0;
}

void step_grid(const Grid *grid, Grid *dst) {
  copy_grid(grid, dst);
  for (int y = 0; y < grid->height; y++) {
    for (int x = 0; x < grid->width; x++) {
      int n = grid_pos_neighbours(grid, x, y);
      bool at = at_grid_pos(grid, x, y);
      if (at == 1 && (n != 2 && n != 3))
        set_grid_pos(dst, x, y, false);
      if (at == 0 && n == 3)
        set_grid_pos(dst, x, y, true);
    }
  }
}

int mod(int a, int b) {
  int r = a % b;
  return r < 0 ? r + b : r;
}

void get_wrapped_grid_pos(const Grid *grid, int *x, int *y) {
  if (!(grid && x && y)) return;
  *x = mod(*x, grid->width);
  *y = mod(*y, grid->height);
}

bool at_grid_pos(const Grid *grid, int x, int y) {
  if (!grid) return false;
  get_wrapped_grid_pos(grid, &x, &y);
  return grid->data[y * grid->width + x];
}

void set_grid_pos(Grid *grid, int x, int y, bool value) {
  if (!grid) return;
  get_wrapped_grid_pos(grid, &x, &y);
  grid->data[y * grid->width + x] = value;
}

int grid_pos_neighbours(const Grid *grid, int x, int y) {
  int count = 0;
  for (int dy = -1; dy < 2; dy++) {
    for (int dx = -1; dx < 2; dx++) {
      if (dy == 0 && dx == 0) continue;
      if (at_grid_pos(grid, x + dx, y + dy))
        count++;
    }
  }
  return count;
}

void print_grid(const Grid *grid) {
  if (!grid) return;
  char *out_str = malloc((2 * grid->height * grid->width + grid->height) * sizeof(char));
  if (!out_str) return;
  int offset = 0;
  for (size_t y = 0; y < grid->height; y++) {
    for (size_t x = 0; x < grid->width; x++) {
      const char *tmp = grid->data[y * grid->width + x] ? "# " : ". ";
      int cur = (int)(y * grid->width + x) * 2;
      strcpy(out_str + cur + offset, tmp);
    }
    out_str[(1 + y) * grid->width * 2 + offset] = '\n';
    offset += 1;
  }
  printf("%s\n", out_str);
  free(out_str);
}

void copy_grid(const Grid *src, Grid *dst) {
  dst->width = src->width;
  dst->height = src->height;
  dst->wrap = src->wrap;
  memcpy(dst->data, src->data, sizeof(bool) * dst->height * dst->width);
}
