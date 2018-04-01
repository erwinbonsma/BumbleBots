/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#ifndef __OBJECTS_INCLUDED
#define __OBJECTS_INCLUDED

#include <Gamebuino-Meta.h>

#include "Utils.h"

//-----------------------------------------------------------------------------
// Object declaration

class Object {
  friend class Tiles;

protected:
  int8_t _tileIndex;
  int8_t _objectIndex;

public:
  /* Initialise one-off state.
   */
  virtual void init(int8_t objectIndex);

  /* Invoked each time a level starts.
   */
  virtual void reset() {}

  int8_t index() { return _objectIndex; }

  virtual ObjectType objectType() = 0;

  virtual void visit(int8_t moverIndex) {}
  virtual void draw(int8_t x, int8_t y) = 0;
};

//-----------------------------------------------------------------------------
// Pickup declaration

class Pickup : public Object {
public:
  ObjectType objectType() { return TYPE_PICKUP; }

  void visit(int8_t moverIndex);
  void draw(int8_t x, int8_t y);
};

//-----------------------------------------------------------------------------
// Teleport declaration

class Teleport : public Object {
  uint8_t _paletteIndex;
  int8_t _destTileIndex;

  uint8_t _coolDownCount;

public:
  void init(int8_t objectIndex, int8_t destTileIndex, uint8_t paletteIndex);

  ObjectType objectType() { return TYPE_TELEPORT; }

  void reset();
  void visit(int8_t moverIndex);
  void draw(int8_t x, int8_t y);
};

//-----------------------------------------------------------------------------
// MenuDigit declaration

class MenuDigit : public Object {
  // Index in the array specifying how to draw this (part of) the digit
  uint8_t _specsStartIndex;
  ColorIndex _color;

public:
  void init(int8_t objectIndex, uint8_t digit, bool topPart, ColorIndex color);

  ObjectType objectType() { return TYPE_MENUDIGIT; }

  void draw(int8_t x, int8_t y);
};

#endif
