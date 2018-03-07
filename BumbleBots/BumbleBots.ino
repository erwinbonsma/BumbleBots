#include <Gamebuino-Meta.h>

#include "ImageData.h"
#include "Palettes.h"

class Mover {

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


Bot::Bot() {
  rotation = 0;
  rotationDir = 0;

  rotationDelay = 2;
  rotationTurn = 5 * rotationDelay;
  rotationMax = 4 * rotationTurn;
}

void Bot::turnStep() {
  rotation += rotationDir + rotationMax;
  rotation %= rotationMax;

  if (rotation % rotationTurn == 0) {
    // Finished turn
    rotationDir = 0;
  }
}

bool Bot::canStartMove() {
  return !isTurning();
}

Color* Bot::getBotPalette(bool flipped) {
  return (flipped) ? flippedBotPalette : defaultPalette;
}

void Bot::update() {
  if (isTurning()) {
    turnStep();
  }
}

void Bot::draw(uint8_t x, uint8_t y) {
  uint8_t r = floor(rotation / rotationDelay);


  botImage.setFrame(r % 10);
  gb.display.colorIndex = getBotPalette(r > 9);

  gb.display.drawImage(x, y, botImage);

  gb.display.colorIndex = defaultPalette;
}



void Player::update() {
  if (gb.buttons.held(BUTTON_LEFT, 0)) {
    nextRotationDir = -1;
  }
  else if (gb.buttons.held(BUTTON_RIGHT, 0)) {
    nextRotationDir = 1;
  }

  if (canStartMove()) {
    if (nextRotationDir != 0) {
      rotationDir = nextRotationDir;
      nextRotationDir = 0;
    }
  }

  Bot::update();
}

Color* Enemy::getBotPalette(bool flipped) {
  return flipped ? flippedEnemyPalette : enemyPalette;
}

Player player = Player();
Enemy enemy = Enemy();

void setup() {
  gb.begin();

  initPalettes();
}

void loop() {
  while(!gb.update());

  gb.display.clear();

  player.update();
  player.draw(36, 37);
  enemy.draw(50, 37);
}
