/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#ifndef __UTILS_INCLUDED
#define __UTILS_INCLUDED

#include <Gamebuino-Meta.h>

const uint8_t maxCols = 8;
const uint8_t maxRows = 8;
const uint8_t maxTiles = maxCols * maxRows;

typedef int8_t Heading;
const int8_t NORTH_EAST = 0;
//const int8_t SOUTH_EAST = 1;
//const int8_t SOUTH_WEST = 2;
//const int8_t NORTH_WEST = 3;

/* Valid values: 0..maxCols * maxRows - 1
 * Using signed to enable more efficient iteration (and support for off-map positions)
 */
typedef int8_t TilePos;

/* Use when tile position/index is unset.
 *
 * It does not correspond to either a valid on-map or off-map position.
 */
const int8_t NO_TILE = 0xff;

int8_t distance(TilePos pos1, TilePos pos2);

inline bool isPosOnMap(TilePos pos) {
  return pos >= 0;
}

/* Functions below can only be used for positions on the map.
 *
 * A position is on the map when:
 *   0 <= col < 8
 *   0 <= row < 8
 */
inline int8_t colOfPos(TilePos pos) {
  return pos & 0x07;
}
inline int8_t rowOfPos(TilePos pos) {
  return (pos >> 3) & 0x07;
}
inline TilePos makeTilePos(int8_t col, int8_t row) {
  //assert(col & 0xf8 == 0);
  //assert(row & 0xf8 == 0);
  return (row << 3) + col;
}

/* Functions below can only be used for positions off the map.
 *
 * Valid positions are:
 *   col in {-1, 8} and row in [0, 7], or
 *   row in {-1, 8} and col in [0, 7]
 */
TilePos makeOffMapTilePos(int8_t col, int8_t row);
int8_t colOfOffMapPos(TilePos pos);
int8_t rowOfOffMapPos(TilePos pos);

/* Functions below can only be used for any map position.
 */
TilePos makeAnyTilePos(int8_t col, int8_t row);
int8_t colOfAnyPos(TilePos pos);
int8_t rowOfAnyPos(TilePos pos);

// Exclusive
const TilePos maxTilePos = maxCols * maxRows;

// column Delta for heading
extern const int8_t colDelta[];

// row Delta for heading
extern const int8_t rowDelta[];

struct ScreenPos {
  int8_t x;
  int8_t y;
};

class LoopHandler {
public:
  virtual void update() = 0;
  virtual void draw() = 0;
};

float smoothClamp(float value);
float smoothStep(float value);

int16_t fastCos(int16_t value);

inline int8_t sign(int8_t value) {
  return (value > 0) - (value < 0);
}

bool isFxPlaying();

void drawDroppingImage(Gamebuino_Meta::Graphics& g, int16_t x, int16_t y, Image& img, int8_t drop);

void assertFailed(const char *function, const char *file, int lineNo, const char *expression);

#define assertTrue(condition) \
if (!(condition)) { \
  assertFailed(__func__, __FILE__, __LINE__, #condition); \
}

#endif
