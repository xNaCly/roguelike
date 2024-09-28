#include "game.h"
#include "display.h"
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

// check if a move is valid, make the move if valid move
void Game_move(Game *g, MOVE m) {
  Position cur = g->player.data.position;
  switch (m) {
  case NORTH:
    if (cur.x != 0) {
      cur.x -= 1;
    } else {
      g->msg = STRING("Hm, I can't seem to go further north.");
    }
    break;
  case SOUTH:
    if (cur.x != COLUMNS - 1) {
      cur.x += 1;
    } else {
      g->msg = STRING("Hm, I can't seem to go further south.");
    }

    break;
  case WEST:
    if (cur.y != 0) {
      cur.y -= 1;
    } else {
      g->msg = STRING("Hm, I can't seem to go further west.");
    }
    break;
  case EAST:
    if (cur.y != ROWS - 1) {
      cur.y += 1;
    } else {
      g->msg = STRING("Hm, I can't seem to go further west.");
    }
    break;
  case INTERACT:
    g->msg = STRING("There is nothing to interact with.");
    break;
  case EXIT:
  case IDLE:
  default: {
  }
  }

  g->player.data.position = cur;
}
