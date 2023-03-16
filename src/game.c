#include "game.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

Game* new_game(int height, int width, bool wrap) {
  Game* game = malloc(sizeof(Game));
  if (!game) return NULL;
  game->height = height;
  game->width = width;
  game->grid = new_grid(height, width, wrap);
  game->buf_grid = new_grid(height, width, wrap);
  return game;
}

void destroy_game(Game* game) {
  destroy_grid(game->grid);
  destroy_grid(game->buf_grid);
  free(game);
}

void run_game(Game* game, int iterations, bool display, int delay) {
  if (!game) return;

  for (size_t i = 0; i < iterations; i++) {
    if (display)
      print_grid(game->grid);
    step_game(game);
    if(display)
      sleep(delay);
  }
}

void step_game(Game* game) {
  if (!game) return;
  step_grid(game->grid, game->buf_grid);
  copy_grid(game->buf_grid, game->grid);
}

void randomize_game(Game* game, float p) {
  randomize_grid(game->grid, p);
}
