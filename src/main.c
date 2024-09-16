#include "types.h"
#include <stdio.h>

int main(void) {
  char *str = "Hello world";
  String *s = String_from(str);
  for (size_t i = 0; i < s->length; i++) {
    char c = s->chars[i];
    printf("%c %d\n", c, c);
  }
  String_free(s);
}
