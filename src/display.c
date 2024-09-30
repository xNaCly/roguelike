#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "display.h"
#include "types.h"

static struct termios orig_termios;

char keybinds[] = {'w', 'a', 's', 'd', 'q', 'e'};
MOVE keybind_to_move[] = {
    ['w'] = NORTH, ['s'] = SOUTH, ['d'] = EAST,
    ['a'] = WEST,  ['q'] = EXIT,  ['e'] = INTERACT,
};
String move_table[] = {
    [NORTH] = STRING("NORTH"),      [SOUTH] = STRING("SOUTH"),
    [WEST] = STRING("WEST"),        [EAST] = STRING("EAST"),
    [EXIT] = STRING("EXIT"),        [IDLE] = STRING("IDLE"),
    [INTERACT] = STRING("INTERACT")};

void Display_move(Display *d, Position p, MOVE m) {
  // resetting the field the player was at before making the current move
  d->matrix[p.x][p.y] = ' ';
  d->last_move = move_table[m];
}

Display *Display_new(void) {
  Display *d = malloc(sizeof(Display));
  ASSERT(d != NULL);
  d->last_move = STRING("IDLE");
  d->matrix = malloc(sizeof(char *) * COLUMNS);
  ASSERT(d->matrix != NULL);

  for (size_t col = 0; col < COLUMNS; col++) {
    d->matrix[col] = malloc(sizeof(char) * ROWS);
    putc(0xA, stdout);
  }

  // enable raw mode
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  // disable buffering
  setvbuf(stdout, NULL, _IONBF, 0);
  return d;
}

// clears the screen, resets all matrix fields, prints the header, renders the
// player/enemies/walls
void Display_render(Display *d, Game *g) {
  printf(ESCAPE_CODE_CLEAR ESCAPE_CODE_HIDE_CURSOR);
  EntityData ed = g->player.data;
  Position p = ed.position;
  // header
  printf("Level: %llu - %s at %zux%zu - Last move: %s\n", g->player.level,
         ed.name.chars, p.x + 1, p.y + 1, d->last_move.chars);

  // resetting the field
  for (size_t col = 0; col < COLUMNS; col++) {
    for (size_t row = 0; row < ROWS; row++) {
      d->matrix[col][row] = ' ';
    }
  }

  // field
  d->matrix[p.x][p.y] = '@';
  for (size_t col = 0; col < COLUMNS; col++) {
    for (size_t row = 0; row < ROWS; row++) {
      putc(d->matrix[col][row], stdout);
    }
    putc('\n', stdout);
  }

  if (g->msg.length) {
    printf("%s: ", g->player.data.name.chars);
    puts(g->msg.chars);
  }

  printf("binds: ");
  // available moves
  for (u32 i = 0; i < sizeof(keybinds); i++)
    printf("[%c] %s ", keybinds[i],
           move_table[keybind_to_move[(u32)keybinds[i]]].chars);
}

// removes all printed characters, reenables the terminal buffering, disables
// raw mode and frees all allocated display memory
void Display_destroy(Display *d) {
  printf(ESCAPE_CODE_CLEAR ESCAPE_CODE_SHOW_CURSOR);
  ASSERT(d != NULL);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); // disable raw mode
  // enable buffering
  setvbuf(stdout, NULL, _IOLBF, 0);
  ASSERT(d->matrix != NULL);
  for (size_t col = 0; col < COLUMNS; col++) {
    free(d->matrix[col]);
  }
  free(d->matrix);
  free(d);
}
