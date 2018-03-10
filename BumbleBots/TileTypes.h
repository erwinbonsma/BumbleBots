#include <Gamebuino-Meta.h>

const uint8_t TILEFLAG_SPRITE_REPEAT = 0x01;
const uint8_t TILEFLAG_CHECKERED = 0x02;

struct TileType {
  const uint8_t spriteIndex;
  const uint8_t spriteHeight;
  const uint8_t spriteYDelta;
  const uint8_t paletteIndex;
  const uint8_t height0;
  const uint8_t flexibility;
  const uint8_t flags;
};

const uint8_t numTileTypes = 2;
extern TileType tileTypes[numTileTypes];
