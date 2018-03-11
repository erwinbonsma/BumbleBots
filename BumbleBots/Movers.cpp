#include "Movers.h"

#include "Globals.h"
#include "ImageData.h"
#include "Palettes.h"

// Exposed in Globals.h
uint8_t numMovers = 0;
Mover* movers[maxNumMovers];

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

const Color* Bot::getBotPalette(bool flipped) {
  return (flipped) ? palettes[PALETTE_FLIPPED_BOT] : palettes[PALETTE_DEFAULT];
}

void Bot::update() {
  if (isTurning()) {
    turnStep();
  }
}

void Bot::draw(uint8_t x, uint8_t y) {
  uint8_t r = floor(rotation / rotationDelay);

  botImage.setFrame(r % 10);
  gb.display.colorIndex = (Color *)getBotPalette(r > 9);

  // TODO: Check why offset is necessary
  gb.display.drawImage(x + 1, y - 1, botImage);

  gb.display.colorIndex = (Color *)palettes[PALETTE_DEFAULT];
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

const Color* Enemy::getBotPalette(bool flipped) {
  return flipped ? palettes[PALETTE_FLIPPED_ENEMY] : palettes[PALETTE_ENEMY];
}
