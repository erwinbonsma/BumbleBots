#include <Gamebuino-Meta.h>

#include "Utils.h"

class Tile;

//-----------------------------------------------------------------------------
// Mover declaration

class Mover {
  friend class Tiles;
  friend class Player; // TMP

  int8_t _moverIndex;
  int8_t _drawTileIndex;
  int8_t _tileIndex;
  int8_t _tileIndex2;

  uint8_t _movementDelay; // >=1, higher value means slower movement
  uint8_t _movementMax;

  int8_t _height;

protected:
  // Movement
  int8_t _movementDir; // -1, 0, 1
  int8_t _movement; // <-movementMax .. movementMax]
  int8_t _movementInc; // -1, 1

  int8_t _dx;
  int8_t _dy;

  // Delta wrt to drawTile
  int8_t _heightDelta;

  virtual bool canMove() { return true; }
  bool isMoving() { return _movementDir; }
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

  bool canEnterTile(int8_t tileIndex);
  void enteringTile(int8_t tileIndex);
  virtual void swapTiles();
  void exitedTile();

public:
  Mover();

  int8_t index() { return _moverIndex; }
  void setIndex(int8_t moverIndex);

  virtual void update();
  virtual void draw(int8_t x, int8_t y) = 0;
};

//-----------------------------------------------------------------------------
// Bot declaration

class Bot : public Mover {

protected:
  // Rotation
  uint8_t rotation;      // [0 .. rotationMax >
  int8_t rotationDir;   // -1, 0, 1

  // Rotation speed
  uint8_t rotationDelay; // >= 1, higher value means slower turning

  // Amount of steps to complete a turn (derived from rotationDelay)
  uint8_t rotationTurn;
  // Maximum rotation value (derived from rotationTurn)
  uint8_t rotationMax;

  int8_t _dazed;

  void bump();
  bool isDazed() { return _dazed > 0; }

  Heading heading();

  bool isTurning() { return rotationDir != 0; }
  void turnStep();

  bool canMove();
  bool canStartMove();

  /* Returns the palette to use for drawing the Bot.
   * The "flipped" argument specifies if the front and rear lights should be switched.
   */
  virtual const Color* getBotPalette(bool flipped);

public:
  Bot();

  void update();
  void draw(int8_t x, int8_t y);
};

//-----------------------------------------------------------------------------
// Player declaration

class Player : public Bot {
  int8_t _nextRotationDir;
  bool _swappedTiles;

protected:
  void swapTiles();

public:
  void update();
};

//-----------------------------------------------------------------------------
// Enemy declaration

class Enemy : public Bot {
protected:
  const Color* getBotPalette(bool flipped);
};
