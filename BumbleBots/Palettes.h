#include <Gamebuino-Meta.h>

const uint8_t numPalettes = 5;

const uint8_t PALETTE_DEFAULT = 0;
const uint8_t PALETTE_FLIPPED_BOT = 1;
const uint8_t PALETTE_ENEMY = 2;
const uint8_t PALETTE_FLIPPED_ENEMY = 3;
const uint8_t PALETTE_DARK_CHECKERED_TILE = 4;

extern const Color palettes[numPalettes][16];
