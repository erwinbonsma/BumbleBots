/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Utils.h"

// column Delta for heading
const int8_t colDelta[] = {0, 1, 0, -1 };

// row Delta for heading
const int8_t rowDelta[] = {-1, 0, 1, 0 };


int8_t distance(TilePos pos1, TilePos pos2) {
  return (
    abs(colOfPos(pos1) - colOfPos(pos2)) +
    abs(rowOfPos(pos1) - rowOfPos(pos2))
  );
}


TilePos makeOffMapTilePos(int8_t col, int8_t row) {
  if (col < 0 || col >= 8) {
    if (col < 0) {
      return 0x80 | (row & 0x07);
    }
    else {
      return 0x90 | (row & 0x07);
    }
  }
  else {
    if (row < 0) {
      return 0xa0 | (col & 0x07);
    }
    else {
      return 0xb0 | (col & 0x07);
    }
  }
}

int8_t colOfOffMapPos(TilePos pos) {
  if (pos & 0x20) {
    return pos & 0x07;
  }
  else {
    return (pos & 0x10) ? 8 : -1;
  }
}

int8_t rowOfOffMapPos(TilePos pos) {
  if (pos & 0x20) {
    return (pos & 0x10) ? 8 : -1;
  }
  else {
    return pos & 0x07;
  }
}

TilePos makeAnyTilePos(int8_t col, int8_t row) {
  if (col < 0 || col >= 8 || row < 0 || row >= 8) {
    return makeOffMapTilePos(col, row);
  }
  return makeTilePos(col, row);
}

int8_t colOfAnyPos(TilePos pos) {
  return isPosOnMap(pos) ? colOfPos(pos) : colOfOffMapPos(pos);
}
int8_t rowOfAnyPos(TilePos pos) {
  return isPosOnMap(pos) ? rowOfPos(pos) : rowOfOffMapPos(pos);
}


const float clampLimit = 12;

float smoothClamp(float value) {
  float vn = value / clampLimit;
  float f = vn/sqrt(vn*vn + 1);
  return f * clampLimit;
}

/* Source: https://en.wikipedia.org/wiki/Smoothstep
 */
float smoothStep(float value) {
  float vn = 0.5 * (value / clampLimit + 1);
  vn = max(0, min(1, vn));
  float f = vn * vn * (3 - 2 * vn);
  return (f * 2 - 1) * clampLimit;
}

const uint8_t fastCosTableSize = 32;
const uint8_t fastCosTable[fastCosTableSize + 1] = {
  255,
  255,
  254,
  252,
  250,
  247,
  244,
  240,
  236,
  231,
  225,
  219,
  212,
  205,
  197,
  189,
  180,
  171,
  162,
  152,
  142,
  131,
  120,
  109,
  98,
  86,
  74,
  62,
  50,
  37,
  25,
  13,
  0
};

/* Fast Cosine function approximation.
 * It is not very accurate, but that's okay.
 *
 * Note: The period of this function is 256
 * It returns values in range of -255..255
 */
int16_t fastCos(int16_t value) {
  // Ensure value is in range [0..128>
  value = abs(value / 2) % 128;

  // Exploit symmetry
  if (value >= 64) {
    value = 128 - value;
  }
  if (value <= 32) {
    return fastCosTable[value];
  }
  else {
    return -(int16_t)fastCosTable[64 - value];
  }
}

namespace Gamebuino_Meta {
  extern FX_Channel fx_channel; // Declared in src/utility/Sound/Sound.cpp
}

/* Inspects Gamebuino internals to determine if a sound effect started via
 * gb.sound.fx is still playing.
 */
bool isFxPlaying() {
  return (
    Gamebuino_Meta::fx_channel.handler != nullptr &&
    Gamebuino_Meta::fx_channel.handler->_current_Sound_FX_time != UINT32_MAX
  );
}

/* Based on Graphics::indexTo565
 *
 * Modified to support drawing of "dropping" images using a mask
 */
void maskedIndexTo565(uint16_t *dest, uint8_t *src, uint8_t *msk, Color *index, uint16_t length, bool skipFirst) {
  uint8_t srcVal = *(src++);
  uint8_t mskVal = *(msk++);

  for (uint16_t i = 0; i < length; i++) {
    if (skipFirst) {
      if (mskVal & 0x0F) {
        dest[i] = (uint16_t)index[srcVal & 0x0F];
      }
      else {
        dest[i] = 0;
      }
      srcVal = *(src++);
      mskVal = *(msk++);
    } else {
      if (mskVal >> 4) {
        dest[i] = (uint16_t)index[srcVal >> 4];
      }
      else {
        dest[i] = 0;
      }
    }
    skipFirst = !skipFirst;
  }
}

/* Based on Graphics::drawImage(int16_t x, int16_t y, Image&)
 *
 * Modified to support drawing of "dropping" images. The significant changes
 * are marked using ADDED and CHANGED in comments.
 */
void drawDroppingImage(Gamebuino_Meta::Graphics& g, int16_t x, int16_t y, Image& img, int8_t drop) {
  int16_t w1 = img._width;
  int16_t h1 = img._height;
  if ((x > g._width) || ((x + w1) < 0) || (y > g._height) || ((y + h1) < 0)) {
    return;
  }

  // Horizontal cropping
  int16_t i2offset = 0;
  int16_t w2cropped = w1;
  if (x < 0) {
    i2offset = -x;
    w2cropped = w1 + x;
    if (w2cropped > g._width) {
      w2cropped = g._width;
    }
  } else if ((x + w1) > g._width) {
    w2cropped = g._width - x;
  }

  // Vertical cropping
  int16_t j2offset = 0;
  int16_t h2cropped = h1;
  if (y < 0) {
    j2offset = -y;
    h2cropped = h1 + y;
    if (h2cropped > g._height) {
      h2cropped = g._height;
    }
  } else if ((y + h1) > g._height) {
    h2cropped = g._height - y;
  }
  h2cropped -= drop; // ADDED

  // Only support these modes
  assertTrue(img.colorMode == ColorMode::index);
  assertTrue(g.colorMode == ColorMode::rgb565);

  uint16_t transparent_backup = img.transparentColor;
  // Only support BLACK as transparent (index) color
  assertTrue(img.useTransparentIndex);
  assertTrue(img.transparentColorIndex == (uint8_t)INDEX_BLACK);
  img.transparentColor = 0; // Same as: (uint16_t)g.colorIndex[img.transparentColorIndex];

  uint16_t destLineArray[w2cropped];
  uint16_t *destLine = destLineArray;
  for (int j2 = 0; j2 < h2cropped; j2++) {
    uint8_t *srcLine = (uint8_t*)img._buffer + ((w1 + 1) / 2) * (j2 + j2offset) + (i2offset / 2);
    uint8_t *mskLine = srcLine + ((w1 + 1) / 2) * drop; // ADDED

    maskedIndexTo565(destLine, srcLine, mskLine, g.colorIndex, w2cropped, i2offset % 2); // CHANGED

    g.drawBufferedLine(x + i2offset, y + j2offset + j2, destLine, w2cropped, img);
  }
  img.transparentColor = transparent_backup;
}

//-----------------------------------------------------------------------------
/* Wrapper around Gamebuino's gb.display.drawFastHLine.
 *
 * Arguments are adapted to ensure that the entire line fits on the screen. If
 * this is not done, it can cause rendering artifacts. This happens when x < 0
 * and x + w == 0. This wrapper function does not take any chances and also
 * handles the other cases where (part of) the line is invisible.
 */
void safeDrawFastHLine(int16_t x, int16_t y, int16_t w) {
  if (x < 0) {
    w += x;
    x = 0;
  }
  if (x + w > 80) {
    w = 80 - x;
  }
  if (w > 0 && y >= 0 && y < 64) {
    gb.display.drawFastHLine(x, y, w);
  }
}

void assertFailed(const char *function, const char *file, int lineNo, const char *expression) {
  if (SerialUSB) {
    SerialUSB.println("=== ASSERT FAILED ===");
    SerialUSB.println(function);
    SerialUSB.println(file);
    SerialUSB.println(lineNo, DEC);
    SerialUSB.println(expression);
    SerialUSB.flush();
  }

  while (1) {
    if (gb.update()) {
      gb.display.clear();
      gb.display.setColor(RED);
      gb.display.println("Assert failed:");
      gb.display.println(function);
      gb.display.println(file);
      gb.display.println(lineNo, DEC);
      gb.display.println(expression);
    }
  }
}
