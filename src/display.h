#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

#define COLUMNS 16
#define ROWS 32
#define ESCAPE_CODE_CLEAR "\033[1;1H\033[2J"
#define ESCAPE_CODE_HIDE_CURSOR "\033[?25l"
#define ESCAPE_CODE_SHOW_CURSOR "\033[?25h"

#define ESCAPE_CODE_RESET "\033[0m"
#define ESCAPE_CODE_GRAY "\033[90m"
#define ESCAPE_CODE_BLACK "\033[30m"
#define ESCAPE_CODE_WHITE "\033[37m"
#define ESCAPE_CODE_CYAN "\033[36m"
#define ESCAPE_CODE_BRIGHT_BLUE "\033[94m"
#define ESCAPE_CODE_BRIGHT_YELLOW "\033[93m"
#define ESCAPE_CODE_BRIGHT_RED "\033[31m"
#define ESCAPE_CODE_BG_CYAN "\033[46m"
#define ESCAPE_CODE_BG_BRIGHT_BLUE "\033[104m"
#define ESCAPE_CODE_BG_BRIGHT_YELLOW "\033[43m"
#define ESCAPE_CODE_BG_BRIGHT_RED "\033[41m"

extern String move_table[];
extern char keybinds[6];
extern MOVE keybind_to_move[];

typedef struct Display {
  String last_move;
  char **matrix;
} Display;

Display *Display_new(void);
void Display_render(Display *d, Game *g);
void Display_destroy(Display *d);
void Display_move(Display *d, Position p, MOVE m);

#endif
