#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

String *String_from(char *vec) {
  String *s = malloc(sizeof(String));
  i32 len = 1;
  while ((*vec++)) {
    len++;
  }
  s->chars = malloc(sizeof(char) * len);
  if (s->chars == NULL) {
    err("Failed to allocate string space")
  }
  vec -= len;
  memcpy(s->chars, vec, len);
  s->length = len - 1;
  return s;
}

void String_free(String *s) {
  free(s->chars);
  s->chars = NULL;
  free(s);
}
