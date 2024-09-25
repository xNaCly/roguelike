#include "display.h"
#include "game.h"
#include "slice.h"
#include "types.h"
#include <unistd.h>

char read_byte(void) {
  char r = -1;
  read(STDIN_FILENO, &r, 1);
  ASSERT(r != -1);
  return r;
}

typedef enum moves {
  NORTH,
  SOUTH,
  WEST,
  EAST,
  IDLE,
} MOVE;

String move_table[] = {
    [NORTH] = STRING("NORTH"), [SOUTH] = STRING("SOUTH"),
    [WEST] = STRING("WEST"),   [EAST] = STRING("EAST"),
    [IDLE] = STRING("IDLE"),
};

// check if a move is valid
void move(Display *d, Game *g, MOVE m) {
  Position cur = g->player.data.position;
  switch (m) {
  case NORTH:
    if (cur.x != 0) {
      cur.x -= 1;
    }
    break;
  case SOUTH:
    if (cur.x != COLUMNS - 1) {
      cur.x += 1;
    }
    break;
  case WEST:
    if (cur.y != 0) {
      cur.y -= 1;
    }
    break;
  case EAST:
    if (cur.y != ROWS - 1)
      cur.y += 1;
    break;
  case IDLE:
  default:
    ERR("impossible");
  }

  // resetting field the player was at before making the current move
  d->matrix[g->player.data.position.x][g->player.data.position.y] = ' ';
  d->last_move = move_table[m];
  g->player.data.position = cur;
}

int main(void) {
  EntityData playerData = (EntityData){
      .position = (Position){.x = 0, .y = 0},
      .name = STRING("Player"),
  };
  Slice *s = Slice_new(8);
  Game g =
      (Game){.player = (Player){.level = 1, .data = playerData}, .enemies = *s};
  Game_load_enemies(&g);

  Display *d = Display_new();
  Display_render(d, &g);

  u8 gameloop = 1;
  while (gameloop) {
    switch (read_byte()) {
    case 'w':
      move(d, &g, NORTH);
      break;
    case 's':
      move(d, &g, SOUTH);
      break;
    case 'a':
      move(d, &g, WEST);
      break;
    case 'd':
      move(d, &g, EAST);
      break;
    case 'q':
      gameloop = 0;
      break;
    default: {
    }
    }
    Display_render(d, &g);
  }

  Display_destroy(d);
  Slice_free(s);
}
