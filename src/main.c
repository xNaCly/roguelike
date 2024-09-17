#include "string.h"
#include <stdio.h>

int main(void) {
  String s = STRING("Hello world");
  puts(s.chars);
  String *s1 = String_from("Hello world 123");
  puts(s1->chars);
  String_free(s1);
}
