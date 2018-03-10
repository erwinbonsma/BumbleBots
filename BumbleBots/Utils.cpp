#include "Utils.h"

// column Delta for heading
const int8_t colDelta[] = {0, 1, 0, -1 };

// row Delta for heading
const int8_t rowDelta[] = {-1, 0, 1, 0 };

uint16_t clockCount = 0;

const float clampLimit = 12;

float smoothClamp(float value) {
  float vn = value / clampLimit;
  float f = vn/sqrt(vn*vn + 1);
  return f * clampLimit;
}

/* Source: https://en.wikipedia.org/wiki/Smoothstep
 */
float smoothStep(float value) {
  float vn = 0.5 * (value / clampLimit + 1);
  vn = max(0, min(1, vn));
  float f = vn * vn * (3 - 2 * vn);
  return (f * 2 - 1) * clampLimit;
}
