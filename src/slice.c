#include "slice.h"
#include "option.h"
#include "types.h"
#include <stdlib.h>
#include <sys/types.h>

Slice *Slice_new(size_t initial_size) {
  Slice *s = malloc(sizeof(Slice));
  ASSERT(s != NULL);
  initial_size = initial_size < SLICE_MIN_SIZE ? SLICE_MIN_SIZE : initial_size;
  s->elements = malloc(sizeof(void *) * initial_size);
  ASSERT(s->elements != NULL);
  s->cap = initial_size;
  s->len = 0;
  return s;
}

static void slice_grow(Slice *s) {
  void **t = malloc(s->cap * SLICE_GROW_FACTOR * sizeof(void *));
  ASSERT(t != NULL);
  for (size_t i = 0; i < s->len; i++) {
    t[i] = s->elements[i];
  }
  free(s->elements);
  s->elements = t;
  s->cap *= SLICE_GROW_FACTOR;
}

void Slice_push(Slice *s, void *element) {
  if (s->len + 1 >= s->cap) {
    slice_grow(s);
  }
  s->elements[s->len++] = element;
}

Option Slice_get(Slice *s, size_t index) {
  if (index >= s->len) {
    return NONE;
  }
  return SOME(s->elements[index]);
}

void Slice_free(Slice *s) {
  if (s->elements != NULL) {
    free(s->elements);
    s->elements = NULL;
  }
  free(s);
}

/* void *Slice_delete(Slice *s, size_t index) { TODO("Slice_delete"); } */
