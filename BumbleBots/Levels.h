#include <Gamebuino-Meta.h>

#include "Utils.h"

struct MapDef {
  const uint8_t numCols;
  const uint8_t numRows;

  /* 1D array for 2D map
   *
   * bits:
   * 7..5 : height (0..7)
   * 4..0 : tileType (0..31)
   */
  const uint8_t tiles[maxCols * maxRows];
};

struct LevelDef {
  const MapDef mapDef;
};

const uint8_t numLevels = 2;
extern const LevelDef levelDefs[numLevels];

