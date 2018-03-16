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

enum class MoverType : int8_t {
  Player,
  Enemy
};
const MoverType TYPE_PLAYER = MoverType::Player;
const MoverType TYPE_ENEMY = MoverType::Enemy;

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


struct ScreenPos {
  int8_t x;
  int8_t y;
};

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
