#include "string.h"
#include "types.h"
#include <sys/types.h>

typedef struct Position {
  u32 x;
  u32 y;
} Position;

typedef struct EntityData {
  Position position;
  String name;
} EntityData;

typedef struct Player {
  EntityData data;
  u64 level;
} Player;

typedef struct Enemy {
  EntityData data;
  f32 gold;
  f32 dps;
  f32 hp;
} Enemy;

typedef struct Game {
  Player player;
  Enemy *Enemies[]; // TODO: convert to a slice
} Game;

#define ENEMY(NAME, HP, DPS, GOLD)                                             \
  (Enemy) {                                                                    \
    .data = (EntityData){.position = (Position){.x = 0, .y = 0},               \
                         .name = STRING(NAME)},                                \
    .gold = GOLD, .dps = DPS, .hp = HP                                         \
  }

void Game_load_enemies(Game *g);
