/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

const uint8_t TILEFLAG_CHECKERED = 0x01;

const ColorIndex NO_TRANSPARANCY = INDEX_BLACK;

const int8_t OFF_MAP_HEIGHT = -64;

struct TileImageSpec {
  const int8_t imageIndex;
  const int8_t frameIndex;
  const int8_t dx;
  const int8_t dy;
};

struct TileType {
  // Image for top of tile, with transparent color
  const TileImageSpec image1;
  // Image for next part of tile, fully opaque
  const TileImageSpec image2;
  // Optional last image
  const TileImageSpec image3;

  const uint8_t paletteIndex;
  const int8_t height0;
  const uint8_t flexibility;
  const uint8_t flags;
};

struct ImageInfo {
  const int8_t dx;
  const int8_t dy;
};

const uint8_t numTileTypes = 34;
const uint8_t TILETYPE_MENU1 = numTileTypes - 2;
const uint8_t TILETYPE_MENU2 = numTileTypes - 1;
extern TileType tileTypes[numTileTypes];

const uint8_t numTileImages = 24;
extern Image tileImages[numTileImages];
