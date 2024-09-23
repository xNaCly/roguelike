#ifndef OPTION_H
#define OPTION_H

#include "string.h"

// similar to the rust type, a union for easier error handling
typedef struct Option {
  void *some;
  u8 none;
} Option;

#define SOME(PTR)                                                              \
  (Option) { .some = PTR }
#define NONE                                                                   \
  (Option) { .none = 1 }
#define UNWRAP(OPTION)                                                         \
  (OPTION.none ? ERR("Unwrapping Option holding a NONE value"),                \
   NULL        : OPTION.some)
#define EXPECT(OPTION, STR) (OPTION.none ? ERR(STR), NULL : OPTION.some)
#define OR(OPTION, OTHER) (OPTION.none ? OTHER : OPTION.some)

#endif
