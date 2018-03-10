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

/* Valid values: 0..maxCols * maxRows - 1
   Using signed to enable more efficient iteration
*/
typedef int8_t MapPos;
inline uint8_t colOfPos(MapPos pos) {
  return pos & 0x07;
}
inline uint8_t rowOfPos(MapPos pos) {
  return (pos >> 3) & 0x07;
}

// Exclusive
const MapPos maxMapPos = maxCols * maxRows;

// column Delta for heading
extern const int8_t colDelta[];

// row Delta for heading
extern const int8_t rowDelta[];

extern uint16_t clockCount;

float smoothClamp(float value);
float smoothStep(float value);

#endif
