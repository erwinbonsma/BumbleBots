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
