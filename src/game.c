#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "grid.h"
#include "gifenc.h"

#ifdef linux
#define OS_WINDOWS 0
#include <time.h>
#endif

#ifdef _WIN32
#define OS_WINDOWS 1
#include <windows.h>
#endif

Game *new_game(int height, int width, bool wrap) {
  Game *game = malloc(sizeof(Game));
  if (!game) return NULL;
  game->height = height;
  game->width = width;
  game->grid = new_grid(height, width, wrap);
  game->buf_grid = new_grid(height, width, wrap);
  game->history_len = 0;
  game->history = NULL;
  return game;
}

void destroy_game(Game *game) {
  destroy_grid(game->grid);
  destroy_grid(game->buf_grid);
  for (int i = 0; i < game->history_len; i++) {
    free(game->history[i]);
  }
  free(game->history);
  free(game);
}

void randomize_game(Game *game, float p) {
  randomize_grid(game->grid, p);
}

void create_game_history(Game *game, int iterations) {
  if (!game)return;
  game->history_len = iterations;
  game->history = malloc(iterations * sizeof(bool*));
  for (int i = 0; i < iterations; i++) {
    game->history[i] = malloc(game->height * game->width * sizeof(bool));
  }
}

void run_game(Game *game, int iterations, bool display, int delay) {
  if (!game) return;
  free(game->history);
  const int grid_size = game->height * game->width;
  create_game_history(game, iterations);

#if !OS_WINDOWS
  struct timespec ts;
  ts = (struct timespec) {0, delay * 1000000};
#endif
  for (size_t i = 0; i < iterations; i++) {
    if (display)
      print_grid(game->grid);
    memcpy(game->history[i], game->grid->data, grid_size * sizeof(bool));
    step_game(game);
    if (display) {
#if OS_WINDOWS
      Sleep(delay);
#else
      nanosleep(&ts, NULL);
#endif
    }
  }
}

void step_game(Game *game) {
  if (!game) return;
  step_grid(game->grid, game->buf_grid);
  copy_grid(game->buf_grid, game->grid);
}

static uint8_t palette[] = {
    0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF,
};

void export_game(Game *game, const int height, const int width) {
  if (!game) return;
  int h_s = height / game->height; 
  int w_s = width / game->width; 
  ge_GIF *g = ge_new_gif("./out.gif",width, height,palette,1,-1,0);
  for (int i = 0; i < game->history_len; i++) {
    for(int y = 0; y < height; y++){
      for (int x = 0; x < width; x++) {
        int n_y = y / h_s;
        int n_x = x / w_s;
        g->frame[y*width+x] = game->history[i][n_y*game->width+n_x];
      }
    }
    ge_add_frame(g, 10);
  }
  ge_close_gif(g);
}
