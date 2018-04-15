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
// ObjectType declaration

enum class ObjectType : int8_t {
  Pickup,
  Teleport,
  Gap,
  Obstacle,
  MenuDigit
};

const ObjectType TYPE_PICKUP = ObjectType::Pickup;
const ObjectType TYPE_TELEPORT = ObjectType::Teleport;
const ObjectType TYPE_GAP = ObjectType::Gap;
const ObjectType TYPE_OBSTACLE = ObjectType::Obstacle;
const ObjectType TYPE_MENUDIGIT = ObjectType::MenuDigit;

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
  virtual bool isElevated() { return false; }

  virtual void visit(int8_t moverIndex) {}
  virtual void draw(int8_t x, int8_t y) = 0;
};

//-----------------------------------------------------------------------------
// Pickup declaration

class Pickup : public Object {
public:
  ObjectType objectType() { return TYPE_PICKUP; }
  bool isElevated() { return true; }

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
// Gap declaration

enum GapState {
  GAP_EMPTY,
  GAP_FILLING,
  GAP_FILLED
};

class Gap : public Object {
  uint8_t _paletteIndex;
  GapState _state;

public:
  void init(int8_t objectIndex, uint8_t paletteIndex);

  ObjectType objectType() { return TYPE_GAP; }

  void fill() { _state = GAP_FILLED; }
  GapState state() { return _state; }

  void reset();
  void visit(int8_t moverIndex);
  void draw(int8_t x, int8_t y);
};

//-----------------------------------------------------------------------------
// Obstacle declaration

struct ObstacleTypeSpec {
  Image& image;
  int8_t dx;
  int8_t dy;
};

const uint8_t numObstacleTypes = 3;
const uint8_t OBSTACLE_ROCK1 = 0;
const uint8_t OBSTACLE_ROCK2 = 1;
const uint8_t OBSTACLE_TREE = 2;
extern const ObstacleTypeSpec obstacleTypes[numObstacleTypes];

class Obstacle : public Object {
  uint8_t _obstacleTypeIndex;
public:
  void init(int8_t objectIndex, uint8_t obstacleTypeIndex);

  ObjectType objectType() { return TYPE_OBSTACLE; }
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
