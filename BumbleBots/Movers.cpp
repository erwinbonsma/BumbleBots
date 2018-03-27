/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Movers.h"

#include "Globals.h"
#include "Images.h"
#include "Palettes.h"
#include "Tiles.h"
#include "Objects.h"

// Exposed in Globals.h
uint8_t numMovers = 0;
Mover* movers[maxNumMovers];

const Gamebuino_Meta::Sound_FX bumpSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,133,-10,0,150,10},
};

const Gamebuino_Meta::Sound_FX moveSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,30,0,0,100,1},
};

bool isFall(int8_t fromTileIndex, int8_t destTileIndex) {
  return (
    tiles->tileAtIndex(fromTileIndex)->height() -
    tiles->tileAtIndex(destTileIndex)->height()
  ) > 6;
}

//-----------------------------------------------------------------------------
// Mover implementation

Mover::Mover() {
  // void
}

void Mover::init(int8_t moverIndex) {
  _moverIndex = moverIndex;
}

void Mover::reset() {
  _tileIndex = NO_TILE;
  _tileIndex2 = NO_TILE;
  _drawTileIndex = NO_TILE;

  _nextMoverIndex = -1;

  _movement = 0;
  _movementDir = 0;
  _movementInc = 1;

  _height = 40;
  _dropSpeed = 6;
  _flags = 0;
}

bool Mover::canMove() {
  return !isFrozen();
}

bool Mover::canStartMove() {
  return (
    canMove() &&
    !isMoving() &&
    !isFalling()
  );
}

Heading Mover::moveHeading() {
  return (Heading)(heading() + _movementDir + _movementInc + 2) % 4;
}

void Mover::updateHeight() {
  int8_t tileHeight = tiles->tileAtIndex(_tileIndex)->height();

  // On two tiles. Height determined by highest one
  if (_tileIndex2 >= 0) {
    tileHeight = max(tileHeight, tiles->tileAtIndex(_tileIndex2)->height());
  }

  if (_height > tileHeight) {
    // Gradual fall
    _height = max(tileHeight, _height - _dropSpeed/4);
    _dropSpeed += 1;
  }
  else {
    _height = tileHeight;
    _dropSpeed = 6;
  }

  _heightDelta = _height - tiles->tileAtIndex(_drawTileIndex)->height();
}

void Mover::updateDxDy() {
  if (isMoving()) {
    Heading h = heading();

    // Direction
    _dx = ((colDelta[h] - rowDelta[h]) * _movementDir);
    _dy = ((colDelta[h] + rowDelta[h]) * _movementDir);

    // Scale and carefully round the delta vectors.
    //
    // Care is taken to ensure that there is a steady rounding rythm. I.e.
    // the period (in update cycles) between changes of the DX and DY values is
    // fixed when the mover moves in a particular direction. This is harder than
    // one might expect, as the _movement argument changes sign when the mover's
    // drawing tile changes. For this reason, rounding is based on the sign of
    // the _movement value.
    //
    // Note: The exact path that a mover traverses depends on its direction.
    // Keeping this the same would further complicate the formula's below which
    // does not seem worth the hassle.
    if (_movement > 0) {
      _dx *= (_movement + 1) / 2;
      _dy *= (_movement + 2) / 4;
    }
    else {
      _dx *= _movement / 2;
      _dy *= (_movement - 1) / 4;
    }
  }
  else {
    _dx = 0;
    _dy = 0;
  }
}

TilePos Mover::drawTilePos() {
  return (TilePos)_drawTileIndex;
}


void Mover::moveStep() {
  _movement += _movementInc;
  int8_t relMov = (_movement * _movementInc + 16) % 16;

  //gb.display.printf("rm=%d,",relMov);
  //gb.display.printf("relMov=%d, hd=%d\n", relMov, moveHeading());
  if (relMov == 3) {
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
  else if (relMov == 8) {
    // Halfway
    swapTiles();
  }
  else if (relMov == 14) {
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
    tiles->tileAtIndex(tileIndex)->height() <=
    tiles->tileAtIndex(_tileIndex)->height()
  );
}

void Mover::enteringTile(int8_t tileIndex) {
  _tileIndex2 = tileIndex;

  TilePos destPos = tiles->posOfTile(_tileIndex2);
  TilePos fromPos = tiles->posOfTile(_tileIndex);

  if (
    colOfAnyPos(destPos) + rowOfAnyPos(destPos) >
    colOfPos(fromPos) + rowOfPos(fromPos)
  ) {
    // Destination tile is in front of current one.
    // Add mover there, to ensure it is drawn on top of both tiles.
    tiles->moveMoverToTile(_moverIndex, destPos);
    _movement -= 16 * sign(_movement);
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
    tiles->moveMoverToTile(_moverIndex, _tileIndex);
    _movement -= 16 * sign(_movement);
  }

  if (isFall(_tileIndex2, _tileIndex)) {
    setFalling();
  }

  _tileIndex2 = NO_TILE;
}

void Mover::update() {
  if (canMove()) {
    if (isMoving()) {
      moveStep();
    }
  }

  updateHeight();
  updateDxDy();

  Tile* tile = tiles->tileAtIndex(_tileIndex);
  if (tile->object() >= 0 && _height == tile->height()) {
    objects[tile->object()]->visit(_moverIndex);
  }

  if (
    isFalling() &&
    // Wait with checking until mover is not on two tiles anymore
    _tileIndex2 == NO_TILE
  ) {
    if (_height - tiles->tileAtIndex(_tileIndex)->height() < 5) {
      // TODO: destroy when falling

      clearFalling();
    }
  }
}

//-----------------------------------------------------------------------------
// Bot implementation

Bot::Bot(uint8_t rotationDelay) :
  Mover(),
  _rotationDelay(rotationDelay),
  _rotationTurn(5 * rotationDelay),
  _rotationMax(20 * rotationDelay) {
  // void
}

void Bot::reset() {
  Mover::reset();

  _rotation = 0;
  _rotationDir = 0;
  _dazed = 0;
}

Heading Bot::heading() {
  return _rotation / _rotationTurn;
}

void Bot::turnStep() {
  _rotation += _rotationDir + _rotationMax;
  _rotation %= _rotationMax;

  if (_rotation % _rotationTurn == 0) {
    // Finished turn
    _rotationDir = 0;
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
  uint8_t r = floor(_rotation / _rotationDelay);

  botImage.setFrame(r % 10);
  gb.display.colorIndex = (Color *)getBotPalette(r > 9);

  gb.display.drawImage(x + _dx + 1, y + _dy - _heightDelta - 1, botImage);
  if (isDazed()) {
    gb.display.drawImage(x + _dx + 2, y + _dy - _heightDelta - 6, dazedImage);
  }

  gb.display.colorIndex = (Color *)palettes[PALETTE_DEFAULT];
}

//-----------------------------------------------------------------------------
// Player implementation

Player::Player() : Bot(2) {}

void Player::swapTiles() {
  Mover::swapTiles();
  _swappedTiles = true;
  gb.sound.fx(moveSfx);
}

void Player::bump() {
  Bot::bump();
  gb.sound.fx(bumpSfx);
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
      _rotationDir = _nextRotationDir;
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
    !isFalling() &&
    _movementDir * _movementInc != desiredMovementDir
  ) {
    // Reverse while moving
    _movementInc = -_movementInc;

    if (_swappedTiles) {
      // Undo swap
      swapTiles();
    }
  }

  _swappedTiles = false;
  Bot::update();

  if (_height < -50) {
    signalDeath("System crash");
  }
}

void Player::drawDebugInfo() {
  gb.display.setCursor(20, 58);
  gb.display.printf("%d/%d\n", isFalling(), canStartMove());
}

//-----------------------------------------------------------------------------
// Enemy implementation

Enemy::Enemy() : Bot(3) {}

void Enemy::init(int8_t moverIndex, int8_t targetIndex) {
  Bot::init(moverIndex);

  _targetIndex = targetIndex;
}

const Color* Enemy::getBotPalette(bool flipped) {
  return flipped ? palettes[PALETTE_FLIPPED_ENEMY] : palettes[PALETTE_ENEMY];
}

void Enemy::bump() {
  Bot::bump();
  _dazed += floor(rand() % 20) - 10;
  _bumpCount += 1;
}

bool Enemy::canEnterTile(int8_t tileIndex) {
  if (
    isBlocked(tileIndex) ||
    !Bot::canEnterTile(tileIndex)
  ) {
    return false;
  }

  Tile* tile = tiles->tileAtIndex(tileIndex);
  if (
    // Another enemy is entering
    tile->isEnemyEntering() ||
    // or already there
    tile->moverOfType(TYPE_ENEMY, _moverIndex) != -1
  ) {
    return false;
  }

  return true;
}

void Enemy::enteringTile(int8_t tileIndex) {
  Bot::enteringTile(tileIndex);
  tiles->tileAtIndex(tileIndex)->setEnemyEntering();
}

void Enemy::exitedTile() {
  Bot::exitedTile();
  tiles->tileAtIndex(_tileIndex)->clearEnemyEntering();
}

void Enemy::turnStep() {
  Bot::turnStep();
  _bumpCount = 0;
}

bool Enemy::isBlocked(int8_t tileIndex) {
  Tile* destTile = tiles->tileAtIndex(tileIndex);

  return (
    // Objects block
    destTile->object() >= 0
  ) || (
    // Fear big falls
    tiles->tileAtIndex(_tileIndex)->height() -
    destTile->height()
  ) > 10;
}

int8_t Enemy::headingScore(Heading h) {
  int8_t destTileIndex = tiles->neighbour(_tileIndex, h);

  if (
    !isPosOnMap((TilePos)destTileIndex) ||
    tiles->tileAtIndex(destTileIndex)->height() < -5
  ) {
    // Do not move off the map
    return -99;
  }

  int8_t score = 0;
  int8_t targetTileIndex = movers[_targetIndex]->_tileIndex;

  if (
    distance((TilePos)destTileIndex, (TilePos)targetTileIndex) <
    distance((TilePos)_tileIndex, (TilePos)targetTileIndex)
  ) {
    // Reward getting closer
    score += 4;
  }

  if (h == heading()) {
    if (_bumpCount < 3) {
      // Prefer moving straight
      score += 1;
    }
    else {
      // Unless that failed three times in a row.
      // This is needed to prevent deadlock situations.
      score -= 20;
    }
  }

  if (canEnterTile(destTileIndex)) {
    // Reward possible movement
    score += 2;
  }
  else if (isBlocked(destTileIndex)) {
    score -= 6;
  }
  else {
    // Penalize climbs
    int8_t hDelta = (
      tiles->tileAtIndex(destTileIndex)->height() -
      tiles->tileAtIndex(_tileIndex)->height()
    );
    score -= max(0, min(5, hDelta));
  }

  return score;
}

void Enemy::update() {
  Mover* target = movers[_targetIndex];
  if (
    _tileIndex == target->_tileIndex &&
    !target->isFalling() &&
    abs(_height - target->_height) < 6
  ) {
    signalDeath("Intercepted");
  }

  if (canStartMove()) {
    int8_t bestScore = -127;
    int8_t bestRotationDir;
    for (int8_t rotationDir = -1; rotationDir <= 1; rotationDir++) {
      int8_t h = (heading() + rotationDir + 4) % 4;
      int8_t score = headingScore(h);
      if (score > bestScore) {
        bestRotationDir = rotationDir;
        bestScore = score;
      }
    }

    _rotationDir = bestRotationDir;

    if (!isTurning()) {
      _movementDir = 1;
    }
  }

  Bot::update();
}

//void Enemy::draw(int8_t x, int8_t y) {
//  Bot::draw(x, y);
//
//  gb.display.setColor(INDEX_YELLOW);
//  gb.display.printf("frozen=%d\n", isFrozen());
//}
