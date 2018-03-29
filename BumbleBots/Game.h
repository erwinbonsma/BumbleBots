/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Levels.h"
#include "Animations.h"

class Game : public LoopHandler {
  uint8_t _startLevel;
  int8_t _numLives; // Signed to easily check game over
  uint8_t _levelNum;

  uint16_t _score;
  uint16_t _displayScore;
  uint16_t _levelStartScore;

  Level _level;

  const char *_causeOfDeath;

  DieAnimation _dieAnimation;
  LevelDoneAnimation _levelDoneAnimation;
  LevelStartAnimation _levelStartAnimation;
  GameOverAnimation _gameOverAnimation;

  // The active animation, if any
  Animation *_activeAnimation;

public:
  int8_t numLives() { return _numLives; }
  uint8_t levelNum() { return _levelNum + 1; }
  Level* level() { return &_level; }
  void addToScore(uint8_t inc) { _score += inc; }

  void signalDeath(const char* cause);
  void signalPickupCollected();

  /* Starts a new game.
   */
  Animation* init(uint8_t startLevel);

  /* Initiates Game Over animation
   */
  Animation* gameOver();

  /* Starts or re-starts the current level.
   */
  Animation* restartLevel();

  /* Starts next level.
   */
  Animation* nextLevel();

  void draw();
  void update();
};

extern Game game;

