#include "string.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

String *String_from(const char *vec) {
  String *s = malloc(sizeof(String));
  size_t len = strlen(vec) + 1;
  s->chars = malloc(sizeof(char) * len);
  ASSERT(s->chars != NULL)
  memcpy(s->chars, vec, len);
  s->length = len - 1;
  return s;
}

void String_free(String *s) {
  if (s == NULL) {
    return;
  }
  if (s->chars != NULL) {
    free(s->chars);
    s->chars = NULL;
  }
  free(s);
}
