#include "game.h"
#include "slice.h"

int main(void) {
  Slice *s = Slice_new(8);
  double d = 25;
  Slice_push(s, &d);
  printf("%f\n", *(double *)OR(Slice_get(s, -1), &d));
  printf("%f\n", *(double *)UNWRAP(Slice_get(s, 0)));
  printf("%f\n", *(double *)EXPECT(Slice_get(s, 0), "This should work"));
  Slice_free(s);
}
