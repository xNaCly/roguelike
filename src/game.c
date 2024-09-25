#include "game.h"
#include "slice.h"
#include "types.h"
#include <stdio.h>

static Enemy enemies[] = {
    ENEMY("Tyranid", 50, 5, 10),
};

void Game_load_enemies(Game *g) {
  ASSERT(g != NULL);
  for (size_t i = 0; i < sizeof(enemies) / sizeof(Enemy); i++) {
    Slice_push(&g->enemies, &enemies[i]);
  }
}
