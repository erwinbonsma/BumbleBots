/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

const uint8_t TILEFLAG_SPRITE_REPEAT = 0x01;
const uint8_t TILEFLAG_CHECKERED = 0x02;

const ColorIndex NO_TRANSPARANCY = INDEX_BLACK;

struct TileImageSpec {
  const uint8_t imageIndex;
  const uint8_t frameIndex;
  const int8_t dx;
  const int8_t dy;
};

struct TileType {
  // Image for top of tile, with transparent color
  const TileImageSpec image1;
  // Image for next part of tile, fully opaque
  const TileImageSpec image2;

  const uint8_t paletteIndex;
  const int8_t height0;
  const uint8_t flexibility;
  const uint8_t flags;
};

struct ImageInfo {
  const int8_t dx;
  const int8_t dy;
};

const uint8_t numTileTypes = 23;
const uint8_t TILETYPE_MENU1 = numTileTypes - 2;
const uint8_t TILETYPE_MENU2 = numTileTypes - 1;
extern TileType tileTypes[numTileTypes];

const uint8_t numTileImages = 14;
extern Image tileImages[numTileImages];
