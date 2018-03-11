#include <Gamebuino-Meta.h>

#include <assert.h>

#ifndef __UTILS_INCLUDED
#define __UTILS_INCLUDED

const uint8_t maxCols = 8;
const uint8_t maxRows = 8;

typedef int8_t Heading;
const int8_t NORTH_EAST = 0;
//const int8_t SOUTH_EAST = 1;
//const int8_t SOUTH_WEST = 2;
//const int8_t NORTH_WEST = 3;

/* Valid values: 0..maxCols * maxRows - 1
   Using signed to enable more efficient iteration
*/
typedef int8_t TilePos;
inline int8_t colOfPos(TilePos pos) {
  return pos & 0x07;
}
inline int8_t rowOfPos(TilePos pos) {
  return (pos >> 3) & 0x07;
}
inline TilePos makeTilePos(int8_t col, int8_t row) {
  assert(col & 0xf8 == 0);
  assert(row & 0xf8 == 0);
  (row << 3) + col;
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

inline int8_t sign(int8_t value) {
  return (value > 0) - (value < 0);
}

#endif
