#ifndef STRING_H
#define STRING_H

#include "types.h"

typedef struct String {
  u32 length;
  char *chars;
} String;

// create a String from a c string
#define STRING(STR)                                                            \
  (String) { .length = sizeof(STR), .chars = STR }

String *String_from(const char *vec);
void String_free(String *s);

#endif
