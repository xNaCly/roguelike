#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

#define COLUMNS 32
#define ROWS 64
#define ESCAPE_CODE_CLEAR "\033[1;1H\033[2J"
#define ESCAPE_CODE_HIDE_CURSOR "\033[?25l"
#define ESCAPE_CODE_SHOW_CURSOR "\033[?25h"

typedef struct Display {
  String last_move;
  char **matrix;
} Display;

Display *Display_new(void);
void Display_render(Display *d, Game *g);
void Display_destroy(Display *d);
void Display_move(Display *d, Position p, MOVE m);

#endif
