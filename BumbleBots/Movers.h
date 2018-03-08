#include <Gamebuino-Meta.h>

class MapUnit;

class Mover {
  friend class MapUnit;

  MapUnit *drawUnit;

public:
  virtual void update() = 0;
  virtual void draw(uint8_t x, uint8_t y);
};


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

  bool isTurning() { return rotationDir != 0; }
  void turnStep();

  // Returns true iff Bot can initiate a new move or turn during update
  bool canStartMove();

  /* Returns the palette to use for drawing the Bot.
   * The "flipped" argument specifies if the front and rear lights should be switched.
   */
  virtual Color* getBotPalette(bool flipped);

public:
  Bot();

  void update();
  void draw(uint8_t x, uint8_t y);
};


class Player : public Bot {
  int8_t nextRotationDir;

public:
  void update();
};


class Enemy : public Bot {
protected:
  Color* getBotPalette(bool flipped);
};
