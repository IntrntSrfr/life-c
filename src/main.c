#include "game.h"

int main() {
  Game *game = new_game(128,256, true);
  randomize_game(game, 0.5f);
  // set_grid_pos(game->grid, 12, 12, true);
  // set_grid_pos(game->grid, 13, 11, true);
  // set_grid_pos(game->grid, 13, 12, true);
  // set_grid_pos(game->grid, 14, 12, true);
  run_game(game, 250, false, 250);
  export_game(game, 512,1024);
  destroy_game(game);
}