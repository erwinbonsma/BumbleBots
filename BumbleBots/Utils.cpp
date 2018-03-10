#include "Utils.h"

// column Delta for heading
const int8_t colDelta[] = {0, 1, 0, -1 };

// row Delta for heading
const int8_t rowDelta[] = {-1, 0, 1, 0 };

uint16_t clockCount = 0;

float smoothClamp(float value) {
  float vn = value / 12;
  float f = vn/sqrt(vn*vn + 1);
  return f * 12;
}
