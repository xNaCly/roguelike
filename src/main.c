#include "display.h"
#include "game.h"
#include "slice.h"
#include "types.h"
#include <unistd.h>

char read_byte(void) {
  char r = -1;
  ASSERT(read(STDIN_FILENO, &r, 1) != -1);
  ASSERT(r != -1);
  return r;
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

  while (1) {
    MOVE m = IDLE;
    switch (read_byte()) {
    case 'w':
      m = NORTH;
      break;
    case 's':
      m = SOUTH;
      break;
    case 'a':
      m = WEST;
      break;
    case 'd':
      m = EAST;
      break;
    case 'q':
      goto exit;
    default: {
    };
    }

    Position last = g.player.data.position;
    Game_move(&g, m);
    Display_move(d, last, m);
    Display_render(d, &g);
  }

exit:
  Display_destroy(d);
  Slice_free(s);
}
