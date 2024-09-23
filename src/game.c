#include "game.h"
#include "types.h"

static Enemy enemies[] = {
    ENEMY("Tyranid", 50, 5, 10),
};

void Game_load_enemies(Game *g) {
  ASSERT(g != NULL);
  TODO("Game_load_enemies");
  printf("level: %llu\n", g->player.level);
  for (size_t i = 0; i < sizeof(enemies) / sizeof(Enemy); i++) {
    printf("Enemy \"%s\" loaded\n", enemies[i].data.name.chars);
  }
}
