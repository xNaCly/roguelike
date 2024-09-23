#ifndef SLICE_H
#define SLICE_H

#include "option.h"
#include <sys/types.h>
#define SLICE_MIN_SIZE 8
#define SLICE_GROW_FACTOR 2

typedef struct Slice {
  void **elements;
  size_t len;
  size_t cap;
} Slice;

Slice *Slice_new(size_t initial_size);
void Slice_push(Slice *s, void *element);
Option Slice_get(Slice *s, size_t index);
void Slice_free(Slice *s);
void Slice_delete(Slice *s, size_t index);

#endif
