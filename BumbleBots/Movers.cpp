#include "Movers.h"

#include <assert.h>

#include "Globals.h"
#include "ImageData.h"
#include "Palettes.h"
#include "Tiles.h"

// Exposed in Globals.h
uint8_t numMovers = 0;
Mover* movers[maxNumMovers];

//-----------------------------------------------------------------------------
// Mover implementation

Mover::Mover() {
  _moverIndex = -1;
  _tileIndex = -1;
  _tileIndex2 = -1;
  _drawTileIndex = -1;

  _movement = 0;
  _movementDir = 0;
  _movementInc = 1;
  _movementDelay = 1; //2;
  _movementMax = _movementDelay * 8;

  _height = 40;
}

bool Mover::canStartMove() {
  return (
    canMove() &&
    !isMoving()
    // TODO: Enable this
    // Mover must touch the ground.
    // Using previous tile height, as tile height has already
    // been updated, but mover's height not yet.
    //&& _height == _prevTileHeight
  );
}

Heading Mover::moveHeading() {
  return (Heading)(heading() + _movementDir + _movementInc + 2) % 4;
}

void Mover::updateHeight() {
  int8_t height = tiles->tileAtIndex(_tileIndex)->height();

  // On two tiles. Height determined by highest one
  if (_tileIndex2 >= 0) {
    height = max(height, tiles->tileAtIndex(_tileIndex2)->height());
  }

  // TODO: Implement falling
  _height = height;
  _heightDelta = _height - tiles->tileAtIndex(_drawTileIndex)->height();
}

void Mover::updateDxDy() {
  if (isMoving()) {
    Heading h = heading();
    _dx = floor((colDelta[h] - rowDelta[h]) * _movement / (float)_movementDelay + 0.5) * _movementDir;
    _dy = floor((colDelta[h] + rowDelta[h]) * _movement / (float)_movementDelay / 2 + 0.5) * _movementDir;
  } else {
    _dx = 0;
    _dy = 0;
  }
}

TilePos Mover::drawTilePos() {
  return (TilePos)_drawTileIndex;
}


void Mover::moveStep() {
  _movement += _movementInc;

  int8_t relMov = (_movement * _movementInc + _movementMax) % _movementMax;
  //gb.display.printf("relMov=%d, hd=%d\n", relMov, moveHeading());
  if (relMov == 2 * _movementDelay) {
    // About to enter next tile
    int8_t destTile = tiles->neighbour(_tileIndex, moveHeading());
    if (canEnterTile(destTile)) {
      // Entering destination tile
      enteringTile(destTile);
    }
    else {
      // Cannot move, retreat
      _movementInc = - _movementInc;
      _movement += _movementInc;
      bump();
    }
  }
  else if (relMov == 4 * _movementDelay) {
    // Halfway
    swapTiles();
  }
  else if (relMov == 6 * _movementDelay) {
    exitedTile();
  }
  else if (relMov == 0) {
    // Done
    _movementDir = 0;
    _movementInc = 1;
  }
}

bool Mover::canEnterTile(int8_t tileIndex) {
  return (
    !isPosOnMap(tiles->posOfTile(tileIndex)) ||
    tiles->tileAtIndex(tileIndex)->height() <=
    tiles->tileAtIndex(_tileIndex)->height()
  );
}

void Mover::enteringTile(int8_t tileIndex) {
  _tileIndex2 = tileIndex;

  // TODO: Check falling
  TilePos destPos = tiles->posOfTile(_tileIndex2);
  TilePos fromPos = tiles->posOfTile(_tileIndex);

  if (
    colOfAnyPos(destPos) + rowOfAnyPos(destPos) >
    colOfPos(fromPos) + rowOfPos(fromPos)
  ) {
    // Destination tile is in front of current one.
    // Add mover there, to ensure it is drawn on top of both tiles.
    tiles->addMover(destPos, _moverIndex);
    _movement -= _movementMax * sign(_movement);
  }
}

void Mover::swapTiles() {
  int8_t tmp = _tileIndex;
  _tileIndex = _tileIndex2;
  _tileIndex2 = tmp;
}

void Mover::exitedTile() {
  if (_drawTileIndex != _tileIndex) {
    // The mover was not yet added to the new tile. Do so now, now it is not covering the
    // previous tile anymore.
    tiles->addMover(_tileIndex, _moverIndex);
    _movement -= _movementMax * sign(_movement);
  }
  _tileIndex2 = -1;
}

void Mover::setIndex(int8_t moverIndex) {
  assert(_moverIndex == -1);
  _moverIndex = moverIndex;
}

void Mover::update() {
  if (canMove()) {
    if (isMoving()) {
      moveStep();
    }
  }

  updateHeight();
  updateDxDy();

  // TODO: visit objects
  // TODO: destroy when falling
}

//-----------------------------------------------------------------------------
// Bot implementation

Bot::Bot() : Mover() {
  rotation = 0;
  rotationDir = 0;

  rotationDelay = 2;
  rotationTurn = 5 * rotationDelay;
  rotationMax = 4 * rotationTurn;
}

Heading Bot::heading() {
  return rotation / rotationTurn;
}

void Bot::turnStep() {
  rotation += rotationDir + rotationMax;
  rotation %= rotationMax;

  if (rotation % rotationTurn == 0) {
    // Finished turn
    rotationDir = 0;
  }
}

void Bot::bump() {
  _dazed = 20;
}

bool Bot::canMove() {
  return !isDazed() && Mover::canMove();
}

bool Bot::canStartMove() {
  return !isTurning() && Mover::canStartMove();
}

const Color* Bot::getBotPalette(bool flipped) {
  return (flipped) ? palettes[PALETTE_FLIPPED_BOT] : palettes[PALETTE_DEFAULT];
}

void Bot::update() {
  if (_dazed > 0) {
    _dazed--;
  }

  if (isTurning()) {
    turnStep();
  }

  Mover::update();
}

void Bot::draw(int8_t x, int8_t y) {
  uint8_t r = floor(rotation / rotationDelay);

  botImage.setFrame(r % 10);
  gb.display.colorIndex = (Color *)getBotPalette(r > 9);

  gb.display.drawImage(x + _dx, y + _dy - _heightDelta - 1, botImage);
  if (isDazed()) {
    gb.display.drawImage(x + _dx + 2, y + _dy - _heightDelta - 6, dazedImage);
  }

  gb.display.colorIndex = (Color *)palettes[PALETTE_DEFAULT];
}

//-----------------------------------------------------------------------------
// Player implementation

void Player::swapTiles() {
  Mover::swapTiles();
  _swappedTiles = true;
}

void Player::update() {
  int8_t desiredMovementDir = 0;

  if (gb.buttons.held(BUTTON_LEFT, 0)) {
    _nextRotationDir = -1;
  }
  else if (gb.buttons.held(BUTTON_RIGHT, 0)) {
    _nextRotationDir = 1;
  }
  else if (gb.buttons.repeat(BUTTON_UP, 0)) {
    desiredMovementDir = 1;
  }
  else if (gb.buttons.repeat(BUTTON_DOWN, 0)) {
    desiredMovementDir = -1;
  }

  if (canStartMove()) {
    if (_nextRotationDir != 0) {
      rotationDir = _nextRotationDir;
      _nextRotationDir = 0;
    }
    else {
      _movementDir = desiredMovementDir;
    }
  }
  else if (
    isMoving() &&
    desiredMovementDir != 0 &&
    !isDazed() &&
    _movementDir * _movementInc != desiredMovementDir
  ) {
    // Reverse while moving
    _movementInc = -_movementInc;

    if (_swappedTiles) {
      // Undo swap
      swapTiles();
    }
  }

  //gb.display.printf("%d, %d\n", isMoving(), _movement);

  _swappedTiles = false;
  Bot::update();
  //if (_swappedTiles) {
  //  // TODO: Sound effect
  //}

  //gb.display.printf("t1=%d, t2=%d, dt=%d\n", _tileIndex, _tileIndex2, _drawTileIndex);
}

//-----------------------------------------------------------------------------
// Enemy implementation

const Color* Enemy::getBotPalette(bool flipped) {
  return flipped ? palettes[PALETTE_FLIPPED_ENEMY] : palettes[PALETTE_ENEMY];
}
