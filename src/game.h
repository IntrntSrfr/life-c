#ifndef GAME_
#define GAME_

#include "grid.h"
#include <stdbool.h>

typedef struct {
  Grid *grid;
  Grid *buf_grid;
  bool **history;
  int history_len;
  int height;
  int width;
} Game;

Game *new_game(int height, int width, bool wrap);
void destroy_game(Game *game);
void randomize_game(Game *game, float p);
void run_game(Game *game, int iterations, bool display, int delay);
void step_game(Game *game);
void export_game(Game *game, int height, int width);

#endif