#include <Gamebuino-Meta.h>

const uint8_t numPalettes = 4;

const uint8_t PALETTE_DEFAULT = 0;
const uint8_t PALETTE_FLIPPED_BOT = 1;
const uint8_t PALETTE_ENEMY = 2;
const uint8_t PALETTE_FLIPPED_ENEMY = 3;

extern const Color palettes[numPalettes][16];
