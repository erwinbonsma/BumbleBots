/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

const uint8_t numPalettes = 10;

const uint8_t PALETTE_DEFAULT = 0;
const uint8_t PALETTE_FLIPPED_BOT = 1;
const uint8_t PALETTE_ENEMY = 2;
const uint8_t PALETTE_FLIPPED_ENEMY = 3;
const uint8_t PALETTE_DARK_CHECKERED_TILE = 4;
const uint8_t PALETTE_LEVELMENU_TILE1 = 5;
const uint8_t PALETTE_LEVELMENU_TILE2 = 6;
const uint8_t PALETTE_TELEPORT1 = PALETTE_DEFAULT;
const uint8_t PALETTE_TELEPORT2 = 7;
const uint8_t PALETTE_TELEPORT3 = 8;
const uint8_t PALETTE_TELEPORT4 = 9;

extern const Color palettes[numPalettes][16];
