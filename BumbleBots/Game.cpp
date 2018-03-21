#include "Game.h"

#include "ImageData.h"

Game game;

Animation* Game::init() {
  _levelNum = 0;
  _numLives = 3;

  _level.init(&levelSpecs[_levelNum]);

  return restartLevel();
}

Animation* Game::restartLevel() {
  _activeAnimation = _levelStartAnimation.init();
  return _activeAnimation;
}

Animation* Game::nextLevel() {
  _levelNum = (_levelNum + 1 ) % numLevels;
  _level.init(&levelSpecs[_levelNum]);

  return restartLevel();
}

Animation* Game::gameOver() {
  _activeAnimation = _gameOverAnimation.init();
  return _activeAnimation;
}

void Game::signalDeath(const char* cause) {
  _causeOfDeath = cause;
}

const uint16_t pickupCollectedSound[] = {
  0x8141, 0x8005, 0x124, 0x130, 0x238, 0x000
};

void Game::signalPickupCollected() {
  _level.pickupCollected();

  gb.sound.play(pickupCollectedSound);

  if (_level.isCompleted()) {
    _activeAnimation = _levelDoneAnimation.init();
  }
}

void Game::update() {
  if (_activeAnimation) {
    _activeAnimation = _activeAnimation->update();
  }

  _causeOfDeath = 0;
  _level.update();
  if (!_activeAnimation && _causeOfDeath) {
    _numLives--;
    _activeAnimation = _dieAnimation.init(_causeOfDeath);
  }
}

void Game::draw() {
  _level.draw();
  if (_activeAnimation) {
    _activeAnimation->draw();
  }

  for (int8_t i = 0; i < _numLives; i++) {
    gb.display.drawImage(i * 5 + 1, 1, liveIconImage);
  }
}

