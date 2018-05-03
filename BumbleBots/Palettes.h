/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Utils.h"

const uint8_t numPalettes = 18;

const uint8_t PALETTE_DEFAULT = 0;
const uint8_t PALETTE_BOT = 1;
const uint8_t PALETTE_FLIPPED_BOT = 2;
const uint8_t PALETTE_ENEMY = 3;
const uint8_t PALETTE_FLIPPED_ENEMY = 4;
const uint8_t PALETTE_DARK_TILE = 5;
const uint8_t PALETTE_LEVELMENU_TILE1 = 6;
const uint8_t PALETTE_LEVELMENU_TILE2 = 7;
const uint8_t PALETTE_TELEPORT1 = PALETTE_DEFAULT;
const uint8_t PALETTE_TELEPORT2 = 8;
const uint8_t PALETTE_TELEPORT3 = 9;
const uint8_t PALETTE_TELEPORT4 = 10;
const uint8_t PALETTE_TELEPORT5 = 11;
const uint8_t PALETTE_GAP_DEFAULT = 12;
const uint8_t PALETTE_GAP_FILLED = 13;
const uint8_t PALETTE_GAP_BLUE = 14;
const uint8_t PALETTE_GAP_EARTH = 15;
const uint8_t PALETTE_GAP_DARK = 16;
const uint8_t PALETTE_BLUE_TILE = 17;

const uint8_t numPaletteColors = 16;
extern const Color palettes[numPalettes][numPaletteColors];
