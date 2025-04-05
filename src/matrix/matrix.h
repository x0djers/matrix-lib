#include <stdint.h>

#include "../../include/config.h"

typedef struct {
  uint64_t rows;
  uint64_t cols;
  MATRIX_TYPE** data;
} Matrix;

