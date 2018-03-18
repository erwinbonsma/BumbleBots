#include "Objects.h"

#include "Globals.h"
#include "ImageData.h"

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
  // TODO
}

void Pickup::draw(int8_t x, int8_t y) {
  gb.display.drawImage(x, y - 1, pickupImage);
}
