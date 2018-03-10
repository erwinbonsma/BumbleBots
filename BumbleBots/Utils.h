#include <Gamebuino-Meta.h>

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

enum Heading {
  NORTH_EAST = 0,
  SOUTH_EAST = 1,
  SOUTH_WEST = 2,
  NORTH_WEST = 3
};

struct MapPos {
  uint8_t col;
  uint8_t row;
};

// column Delta for heading
extern const int8_t colDelta[];

// row Delta for heading
extern const int8_t rowDelta[];

extern uint16_t clockCount;

float smoothClamp(float value);

#endif
