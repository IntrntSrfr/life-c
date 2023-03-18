#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "grid.h"
#include "gifenc.h"

#ifdef linux
#define OS_WINDOWS 0
#include <unistd.h>
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
  game->history = NULL;
  return game;
}

void destroy_game(Game *game) {
  destroy_grid(game->grid);
  destroy_grid(game->buf_grid);
  free(game->history);
  free(game);
}

void randomize_game(Game *game, float p) {
  randomize_grid(game->grid, p);
}

void create_game_history(Game *game, int iterations) {
  if (!game)return;
  game->history = (bool **) malloc(sizeof(bool *) * iterations + 1);
  for (int i = 0; i < iterations - 1; ++i) {
    game->history[i] = malloc(sizeof(bool *) * game->height * game->width);
  }
}

void run_game(Game *game, int iterations, bool display, int delay) {
  if (!game) return;
  printf("%p\n", game->history);
  free(game->history);
  const int grid_size = game->height * game->width;
  //create_game_history(game, iterations);

#if !OS_WINDOWS
  struct timespec ts;
  if (!OS_WINDOWS)
    ts = (struct timespec) {0, delay * 1000000};
#endif
  for (size_t i = 0; i < iterations; i++) {
    if (display)
      print_grid(game->grid);
    //memcpy(game->history + grid_size * i, game->grid->data, grid_size);
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
  const int game_size = game->height * game->width;
  int iter = 0;
  printf("hello\n");
  for (int i = 0; i < 5; ++i) {
    //bool *data = *(game->history + i);
    for (int j = 0; j < 10; ++j) {
      //printf("ye: %d\n", *(data + j));
    }
    //printf("%p\n", *game->history+i);
  }

  /*while(game->history+iter){
    printf("hello\n");
    iter++;
  }
  */
  //ge_GIF *g = ge_new_gif("./out.gif",150, 150,palette,1,-1,0);
}
