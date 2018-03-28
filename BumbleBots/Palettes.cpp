/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Palettes.h"

const Color LBLUE = LIGHTBLUE;
const Color LGREEN = LIGHTGREEN;
const Color DGRAY = DARKGRAY;
const Color DBLUE = DARKBLUE;

const Color palettes[numPalettes][16] = {
  // Default
  { BLACK,  DBLUE,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   WHITE,  RED,    ORANGE, YELLOW, LGREEN, LBLUE,  BLUE,   PINK,   BEIGE },
  // Flipped bot
  { BLACK,  DBLUE,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   WHITE,  YELLOW, ORANGE, RED,    LGREEN, LBLUE,  BLUE,   PINK,   BEIGE },
  // Enemy
  { BLACK,  DGRAY,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   WHITE,  RED,    ORANGE, YELLOW, LGREEN, BEIGE,  BROWN,  PINK,   BEIGE },
  // Flipped enemy
  { BLACK,  DGRAY,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   WHITE,  YELLOW, ORANGE, RED,    LGREEN, BEIGE,  BROWN,  PINK,   BEIGE },
  // Checker tile
  { BLACK,  DBLUE,  PURPLE, GREEN,  BROWN,  BLACK,  DGRAY,  GRAY,   RED,    ORANGE, YELLOW, LGREEN, LBLUE,  BLUE,   PINK,   BEIGE },
  // Level menu, Tile 1
  { BLACK,  DBLUE,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   PURPLE, RED,    ORANGE, YELLOW, LGREEN, LBLUE,  BLUE,   PINK,   BEIGE },
  // Level menu, Tile 2
  { BLACK,  DBLUE,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   GREEN,  RED,    ORANGE, YELLOW, LGREEN, LBLUE,  BLUE,   PINK,   BEIGE },
};
