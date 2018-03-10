#include <Gamebuino-Meta.h>

#ifndef __UTILS_INCLUDED
#define __UTILS_INCLUDED

const uint8_t maxCols = 8;
const uint8_t maxRows = 8;

enum Heading {
  NORTH_EAST = 0,
  SOUTH_EAST = 1,
  SOUTH_WEST = 2,
  NORTH_WEST = 3
};

/* Although col and row are never negative, using signed values to enable more
 * efficient iteration (where a negative value acts as guard).
 */
struct MapPos {
  int8_t col;
  int8_t row;
};

// column Delta for heading
extern const int8_t colDelta[];

// row Delta for heading
extern const int8_t rowDelta[];

extern uint16_t clockCount;

float smoothClamp(float value);

#endif
