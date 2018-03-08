#include "Movers.h"

#include "Palettes.h"
#include "ImageData.h"

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
