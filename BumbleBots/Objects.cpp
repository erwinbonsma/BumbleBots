/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Objects.h"

#include "Globals.h"
#include "Images.h"
#include "Movers.h"
#include "Tiles.h"

// Exposed in Globals.h
uint8_t numObjects = 0;
Object* objects[maxNumObjects];

//-----------------------------------------------------------------------------
// Object implementation

void Object::init(int8_t objectIndex) {
  _objectIndex = objectIndex;
}

//-----------------------------------------------------------------------------
// Pickup implementation

void Pickup::visit(int8_t moverIndex) {
  if (!movers[moverIndex]->isFrozen()) {
    tiles->tileAtIndex(_tileIndex)->removeObject(_objectIndex);
    signalPickupCollected();
  }
}

void Pickup::draw(int8_t x, int8_t y) {
  gb.display.drawImage(x, y - 1, pickupImage);
}

//-----------------------------------------------------------------------------
// MenuDigit implementation

const uint8_t menuDigitsSpecsStart[] = {
  0, 13,
  30, 37,
  50, 61,
  76, 87,
  102, 115,
  128, 139,
  152, 159,
  76, 176,
  185, 159,
  185, 115
};

const uint8_t menuDigitSpecs[] = {
  // Zero, top
  17, 3, 9, 7, 7, 1, 3, 4, 4, 4, 2, 1, 2,
  // Zero, bottom
  3, 3, 2, 4, 5, 4, 4, 3, 4, 4, 1, 4, 6, 5, 6, 1, 5,
  // One, top
  29, 7, 7, 5, 6, 1, 9,
  // One, bottom
  12, 3, 2, 3, 1, 4, 7, 5, 10, 4, 7, 1, 5,
  // Two, top
  17, 3, 12, 4, 11, 4, 3, 5, 2, 1, 2,
  // Two, bottom
  3, 3, 2, 7, 2, 4, 3, 4, 4, 4, 11, 4, 7, 1, 5,
  // Three, top
  17, 3, 12, 4, 11, 4, 4, 4, 2, 1, 2,
  // Three, bottom
  12, 3, 2, 3, 4, 4, 4, 4, 1, 4, 6, 5, 6, 1, 5,
  // Four, top
  17, 3, 9, 4, 10, 1, 4, 3, 4, 4, 2, 1, 2,
  // Four, bottom
  3, 3, 5, 4, 9, 4, 9, 4, 7, 4, 6, 1, 5,
  // Five, top
  17, 3, 9, 7, 7, 1, 3, 4, 7, 1, 5,
  // Five, bottom
  3, 3, 5, 4, 2, 3, 4, 4, 4, 9, 6, 5, 12,
  // Six, top
  17, 3, 9, 4, 10, 1, 20,
  // Six, bottom
  3, 3, 2, 7, 2, 4, 3, 4, 4, 4, 1, 4, 6, 5, 6, 1, 5,
  // Seven, top => Three, top
  // Seven, bottom
  25, 3, 9, 4, 7, 4, 6, 1, 5,
  // Eight, top
  17, 3, 9, 7, 7, 1, 3, 4, 4, 4, 2, 1, 2,
  // Eight, bottom => Six, bottom
  // Nine, top => Eight, top
  // Nine, bottom => Four, bottom
};

struct TileLineSpec {
  uint8_t dx;
  uint8_t len;
};

const uint8_t numTileLines = 8;
const TileLineSpec tileLineSpecs[numTileLines] = {
  TileLineSpec { .dx = 7, .len = 1 },
  TileLineSpec { .dx = 5, .len = 5 },
  TileLineSpec { .dx = 3, .len = 9 },
  TileLineSpec { .dx = 1, .len = 13 },
  TileLineSpec { .dx = 0, .len = 15 },
  TileLineSpec { .dx = 2, .len = 11 },
  TileLineSpec { .dx = 4, .len = 7 },
  TileLineSpec { .dx = 6, .len = 3 },
};

void MenuDigit::init(int8_t objectIndex, uint8_t digit, bool topPart, ColorIndex color) {
  Object::init(objectIndex);

  _specsStartIndex = menuDigitsSpecsStart[digit * 2 + (topPart ? 0 : 1)];
  _color = color;
}

void MenuDigit::draw(int8_t x, int8_t y) {
  uint8_t specIndex = _specsStartIndex;
  uint8_t drawLenRemaining = menuDigitSpecs[specIndex];
  uint8_t lineIndex = 0;
  uint8_t dx = tileLineSpecs[lineIndex].dx;
  uint8_t lineLenRemaining = tileLineSpecs[lineIndex].len;
  bool draw = false;

  x -= 3;
  y += 2;

  gb.display.setColor(_color);
  while (1) {
    //assertTrue(drawLenRemaining > 0);
    //assertTrue(lineLenRemaining > 0);

    uint8_t drawLen = min(drawLenRemaining, lineLenRemaining);
    if (draw) {
      gb.display.drawFastHLine(x + dx, y + lineIndex, drawLen);
    }
    dx += drawLen;
    lineLenRemaining -= drawLen;
    drawLenRemaining -= drawLen;

    if (lineLenRemaining == 0) {
      lineIndex++;
      if (lineIndex == numTileLines) {
        break;
      }
      lineLenRemaining = tileLineSpecs[lineIndex].len;
      dx = tileLineSpecs[lineIndex].dx;
    }

    if (drawLenRemaining == 0) {
      drawLenRemaining = menuDigitSpecs[++specIndex];
      draw = !draw;
    }
  }
}
