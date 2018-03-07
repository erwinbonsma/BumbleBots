#include "Palettes.h"

Color* defaultPalette;
Color* flippedBotPalette;
Color* enemyPalette;
Color* flippedEnemyPalette;

Color* copyPalette(Color* srcPalette) {
  Color* dstPalette = new Color[16];
  memcpy(dstPalette, srcPalette, sizeof(Color) * 16);
  return dstPalette;
}

void initPalettes() {
  defaultPalette = gb.display.colorIndex;

  // Flip front- and rear-light
  flippedBotPalette = copyPalette(defaultPalette);
  flippedBotPalette[(int)INDEX_RED] = YELLOW;
  flippedBotPalette[(int)INDEX_YELLOW] = RED;

  enemyPalette = copyPalette(defaultPalette);
  enemyPalette[(int)INDEX_LIGHTBLUE] = BEIGE;
  enemyPalette[(int)INDEX_BLUE] = BROWN;
  enemyPalette[(int)INDEX_DARKBLUE] = DARKGRAY;

  flippedEnemyPalette = copyPalette(enemyPalette);
  flippedEnemyPalette[(int)INDEX_RED] = YELLOW;
  flippedEnemyPalette[(int)INDEX_YELLOW] = RED;
}
