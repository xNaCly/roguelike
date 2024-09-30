#include "display.h"
#include "game.h"
#include "slice.h"
#include "string.h"
#include "types.h"
#include <unistd.h>

i32 read_char(void) {
  char r = -1;
  ASSERT(read(STDIN_FILENO, &r, 1) != -1);
  ASSERT(r != -1);
  return (i32)r;
}

int main(void) {
  String *username = String_from(getlogin());
  EntityData playerData = (EntityData){
      .position = (Position){.x = 0, .y = 0},
      .name = *username,
  };
  Slice *enemies = Slice_new(8);
  Game g = (Game){
      .player = (Player){.level = 1, .data = playerData},
      .enemies = *enemies,
      .msg = STRING(
          "I think i have to advance through the rooms to climb the tower")};
  Game_load_enemies(&g);

  Display *d = Display_new();
  Display_render(d, &g);

  while (1) {
    MOVE m = IDLE;
    i32 action = read_char();
    u8 isValidAction = 0;
    for (u32 i = 0; i < sizeof(keybinds); i++) {
      if (action == keybinds[i]) {
        isValidAction = 1;
      }
    }

    if (isValidAction) {
      m = keybind_to_move[action];
      if (m == EXIT) {
        goto exit;
      }
    } else {
      g.msg = STRING("I don't know what to do with this action");
    }

    Position last = g.player.data.position;
    Game_move(&g, m);
    Display_move(d, last, m);
    Display_render(d, &g);
  }

exit:
  String_free(username);
  Display_destroy(d);
  Slice_free(enemies);
}
