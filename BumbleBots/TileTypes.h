#include <Gamebuino-Meta.h>

const uint8_t TILEFLAG_SPRITE_REPEAT = 0x01;
const uint8_t TILEFLAG_CHECKERED = 0x02;

const ColorIndex NO_TRANSPARANCY = INDEX_BLACK;

struct TileType {
  // Top part of image, with transparent color
  const uint8_t topImageIndex;
  const uint8_t topFrameIndex;
  // Bottom part of image, fully opaque
  const uint8_t bottomImageIndex;
  const uint8_t bottomFrameIndex;

  const uint8_t paletteIndex;
  const int8_t height0;
  const uint8_t flexibility;
  const uint8_t flags;
};

struct ImageInfo {
  const int8_t dx;
  const int8_t dy;
};

const uint8_t numTileTypes = 11;
extern TileType tileTypes[numTileTypes];

const uint8_t numTileImages = 8;
extern ImageInfo tileImageInfo[numTileImages];
extern Image tileImages[numTileImages];
