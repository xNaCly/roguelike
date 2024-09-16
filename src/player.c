#include "types.h"
#include <sys/types.h>

typedef struct Position {
  u64 x;
  u64 y;
} Position;

typedef struct Player {
  Position position;
  u64 level;
} Player;
