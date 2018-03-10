#include "TileTypes.h"

TileType tileTypes[numTileTypes] = {
  // 0: Basic, fixed, light
  TileType {
    .spriteIndex = 2,
    .spriteHeight = 3,
    .spriteYDelta = 0,
    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 0,
    .flags = TILEFLAG_SPRITE_REPEAT
  },

  // 1: Basic, normal flexibilty
  TileType {
    .spriteIndex = 0,
    .spriteHeight = 2,
    .spriteYDelta = 0,
    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 3,
    .flags = TILEFLAG_SPRITE_REPEAT | TILEFLAG_CHECKERED
  }
};

