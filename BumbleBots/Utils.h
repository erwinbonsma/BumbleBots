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
typedef int8_t TilePos;
inline uint8_t colOfPos(TilePos pos) {
  return pos & 0x07;
}
inline uint8_t rowOfPos(TilePos pos) {
  return (pos >> 3) & 0x07;
}

// Exclusive
const TilePos maxTilePos = maxCols * maxRows;

// column Delta for heading
extern const int8_t colDelta[];

// row Delta for heading
extern const int8_t rowDelta[];

float smoothClamp(float value);
float smoothStep(float value);

float fastCos(float value);

#endif
