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
// MoverType declaration

enum class MoverType : int8_t {
  Player,
  Enemy,
  Box
};

const MoverType TYPE_PLAYER = MoverType::Player;
const MoverType TYPE_ENEMY = MoverType::Enemy;
const MoverType TYPE_BOX = MoverType::Box;

//-----------------------------------------------------------------------------
// Mover declaration

const int8_t MOVERFLAG_FALLING = 0x01;
const int8_t MOVERFLAG_FROZEN = 0x02;
const int8_t MOVERFLAG_TELEPORTED = 0x04;
const int8_t MOVERFLAG_DESTROYED = 0x08;
const int8_t MOVERFLAG_FORCEFALL = 0x20; // Only used by Box

class Mover {
  friend class Tile;
  friend class Tiles;
  friend class Teleport;

  // Link to next mover on same tile (if any)
  int8_t _nextMoverIndex;

  int8_t _fallingSpeed;

protected:

  int8_t _moverIndex;
  int8_t _tileIndex;
  int8_t _tileIndex2;

  int8_t _flags;

  // Movement
  int8_t _movementDir; // -1, 0, 1
  int8_t _movement; // <-movementMax .. movementMax]
  int8_t _movementInc; // -1, 1

  int8_t _dx;
  int8_t _dy;
  int8_t _height;
  int8_t _heightDelta;
  int8_t _drawTileIndex;

  int8_t _drop;

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

  virtual void updateHeight();
  void updateDxDy();

  // Tile that the mover is on for drawing purposes
  TilePos drawTilePos() { return (TilePos)_drawTileIndex; }

  // The offset of the mover's screen position wrt to its drawTile
  int8_t dx() { return _dx; }
  int8_t dy() { return _dy; }

  virtual void enteringTile(int8_t tileIndex);
  virtual void swapTiles();
  virtual void exitedTile();

public:
  Mover();
  virtual void init(int8_t moverIndex);
  virtual void reset();

  int8_t index() { return _moverIndex; }
  int8_t tileIndex() { return _tileIndex; }
  TilePos tilePos() { return (TilePos)_tileIndex; }

  virtual MoverType moverType() = 0;

  bool isMoving() { return _movementDir; }

  void freeze() { _flags |= MOVERFLAG_FROZEN; }
  bool isFrozen() { return _flags & MOVERFLAG_FROZEN; }

  // Signals if a mover is falling (onto any tile)
  void setFalling() { _flags |= MOVERFLAG_FALLING; }
  void clearFalling() { _flags &= ~MOVERFLAG_FALLING; }
  bool isFalling() { return _flags & MOVERFLAG_FALLING; }

  void startDrop() { _drop = 1; }
  bool isDropping() { return _drop; }
  int dropDelta() { return min(5, _drop / 4); }

  void setTeleported() { _flags |= MOVERFLAG_TELEPORTED; }
  void clearTeleported() { _flags &= ~MOVERFLAG_TELEPORTED; }
  bool didTeleport() { return _flags & MOVERFLAG_TELEPORTED; }

  void setDestroyed() { _flags |= MOVERFLAG_DESTROYED; }
  bool isDestroyed() { return _flags & MOVERFLAG_DESTROYED; }

  void setHeight(int8_t height);
  int8_t height() { return _height; }

  virtual void destroy();

  virtual bool canEnterTile(int8_t tileIndex);

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

  void enteringTile(int8_t tileIndex);
  void swapTiles();
  void updateHeight();

public:
  Player();

  bool canEnterTile(int8_t tileIndex);
  MoverType moverType() { return TYPE_PLAYER; }

  void reset();
  void update();
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
  void reset();
  void destroy();

  MoverType moverType() { return TYPE_ENEMY; }

  void update();
};

//-----------------------------------------------------------------------------
// Box declaration

class Box : public Mover {

  Heading _heading;

  void setForceFall() { _flags |= MOVERFLAG_FORCEFALL; }
  void clearForceFall() { _flags &= ~MOVERFLAG_FORCEFALL; }
  bool shouldForceFall() { return _flags & MOVERFLAG_FORCEFALL; }

  Heading heading() { return _heading; }
  void setHeading(Heading heading) { _heading = heading; }

protected:
  bool canEnterTile(int8_t tileIndex);
  void enteringTile(int8_t tileIndex);
  void exitedTile();

  void updateHeight();

public:
  MoverType moverType() { return TYPE_BOX; }

  void reset();

  void push(Heading heading);

  void draw(int8_t x, int8_t y);
};

#endif
