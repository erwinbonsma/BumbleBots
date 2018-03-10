#include "TileTypes.h"

TileType tileTypes[numTileTypes] = {
  // 0: Basic, normal flexibilty
  TileType {
    .spriteIndex = 0,
    .spriteHeight = 2,
    .spriteYDelta = 0,
    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 3,
    .flags = TILE_CHECKERED | TILE_CHECKERED
  },

  // 1: Basic, fixed
  TileType {
    .spriteIndex = 2,
    .spriteHeight = 3,
    .spriteYDelta = 0,
    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 3,
    .flags = TILE_CHECKERED | TILE_CHECKERED
  }
};

