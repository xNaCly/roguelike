// types.h is used for types i want in every source file
#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;
typedef signed char i8;
typedef signed int i16;
typedef signed long int i32;
typedef signed long long int i64;
typedef float f32;
typedef double f64;

typedef struct Position {
  u32 x;
  u32 y;
} Position;

typedef enum moves {
  NORTH,
  SOUTH,
  WEST,
  EAST,
  IDLE,
} MOVE;

#define ERR(str)                                                               \
  fprintf(stderr, "panic: %s at %s:%d\n", str, __FILE__, __LINE__),            \
      exit(EXIT_FAILURE)
#define TODO(str)                                                              \
  fprintf(stderr, "TODO: '%s' at %s:%d\n", str, __FILE__, __LINE__),           \
      exit(EXIT_FAILURE)
#define ASSERT(EXP)                                                            \
  if (!(EXP)) {                                                                \
    fprintf(stderr, "Assertion \"" #EXP "\" failed at %s, line %d\n",          \
            __FILE__, __LINE__);                                               \
    exit(EXIT_FAILURE);                                                        \
  }

#endif
