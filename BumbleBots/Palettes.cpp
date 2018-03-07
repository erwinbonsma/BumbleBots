#include "Palettes.h"

Color* defaultPalette;
Color* flippedBotPalette;

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
}
