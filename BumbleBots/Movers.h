/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#ifndef __MOVERS_INCLUDED
#define __MOVERS_INCLUDED

#include <Gamebuino-Meta.h>

#include "Utils.h"

class Tile;

//-----------------------------------------------------------------------------
// Mover declaration

const int8_t MOVERFLAG_FALLING = 0x01;
const int8_t MOVERFLAG_FROZEN = 0x02;

class Mover {
  friend class Tile;
  friend class Tiles;
  friend class Player;
  friend class Enemy;

  int8_t _moverIndex;
  int8_t _drawTileIndex;
  int8_t _tileIndex;
  int8_t _tileIndex2;

  // Link to next mover on same tile (if any)
  int8_t _nextMoverIndex;

  int8_t _height;
  int8_t _dropSpeed;
  int8_t _flags;

protected:

  // Movement
  int8_t _movementDir; // -1, 0, 1
  int8_t _movement; // <-movementMax .. movementMax]
  int8_t _movementInc; // -1, 1

  int8_t _dx;
  int8_t _dy;

  // Delta wrt to drawTile
  int8_t _heightDelta;

  bool isMoving() { return _movementDir; }
  virtual bool canMove();
  // Returns true iff Bot can initiate a new move or turn during update
  virtual bool canStartMove();
  void moveStep();

  virtual void bump() {};

  /* The direction that the mover is facing.
   */
  virtual Heading heading() { return NORTH_EAST; }

  /* Direction the mover is moving in. Undefined when the mover is not currently
   * moving. It is the opposite of heading() when the mover is moving backwards.
   */
  Heading moveHeading();

  void updateHeight();
  void updateDxDy();

  // Tile that the mover is on for drawing purposes
  TilePos drawTilePos() { return (TilePos)_drawTileIndex; }

  // The offset of the mover's screen position wrt to its drawTile
  int8_t dx() { return _dx; }
  int8_t dy() { return _dy; }

  virtual bool canEnterTile(int8_t tileIndex);
  virtual void enteringTile(int8_t tileIndex);
  virtual void swapTiles();
  virtual void exitedTile();

public:
  Mover();
  virtual void init(int8_t moverIndex);
  virtual void reset();

  int8_t index() { return _moverIndex; }
  TilePos tilePos() { return (TilePos)_tileIndex; }

  virtual MoverType moverType() = 0;

  void freeze() { _flags |= MOVERFLAG_FROZEN; }
  bool isFrozen() { return _flags & MOVERFLAG_FROZEN; }

  void setFalling() { _flags |= MOVERFLAG_FALLING; }
  void clearFalling() { _flags &= ~MOVERFLAG_FALLING; }
  bool isFalling() { return _flags & MOVERFLAG_FALLING; }

  virtual void update();
  virtual void draw(int8_t x, int8_t y) = 0;
};

//-----------------------------------------------------------------------------
// Bot declaration

class Bot : public Mover {

protected:
  // Rotation
  uint8_t _rotation;     // [0 .. rotationMax>
  int8_t _rotationDir;   // -1, 0, 1

  // Rotation speed
  const uint8_t _rotationDelay; // >= 1, higher value means slower turning

  // Amount of steps to complete a turn (derived from rotationDelay)
  const uint8_t _rotationTurn;
  // Maximum rotation value (derived from rotationTurn)
  const uint8_t _rotationMax;

  int8_t _dazed;

  virtual void bump();
  bool isDazed() { return _dazed > 0; }

  Heading heading();

  bool isTurning() { return _rotationDir != 0; }
  virtual void turnStep();

  bool canMove();
  bool canStartMove();

  /* Returns the palette to use for drawing the Bot.
   * The "flipped" argument specifies if the front and rear lights should be switched.
   */
  virtual const Color* getBotPalette(bool flipped);

public:
  Bot(uint8_t rotationDelay);

  virtual void reset();

  void update();
  void draw(int8_t x, int8_t y);
};

//-----------------------------------------------------------------------------
// Player declaration

class Player : public Bot {
  int8_t _nextRotationDir;
  bool _swappedTiles;

protected:
  void bump();
  void swapTiles();

public:
  Player();

  MoverType moverType() { return TYPE_PLAYER; }

  void update();

  void drawDebugInfo(); // TMP
};

//-----------------------------------------------------------------------------
// Enemy declaration

class Enemy : public Bot {
  int8_t _targetIndex;
  int8_t _bumpCount;

  /* Returns true iff the enemy is not expected to be able to move to the unit soon.
   */
  bool isBlocked(int8_t tileIndex);

  int8_t headingScore(Heading heading);

protected:
  const Color* getBotPalette(bool flipped);

  void bump();
  bool canEnterTile(int8_t tileIndex);
  void enteringTile(int8_t tileIndex);
  void exitedTile();
  void turnStep();

public:
  Enemy();

  void init(int8_t moverIndex, int8_t targetIndex);

  MoverType moverType() { return TYPE_ENEMY; }

  void update();
//  void draw(int8_t x, int8_t y); // TMP
};

#endif
