/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Levels.h"
#include "Animations.h"

class Game : public LoopHandler {
  int8_t _numLives; // Signed to easily check game over
  uint8_t _levelNum;

  uint16_t _score;
  uint16_t _displayScore;

  Level _level;
  bool _lastLevelCompleted;

  const char *_causeOfDeath;

  DieAnimation _dieAnimation;
  LevelDoneAnimation _levelDoneAnimation;
  LevelStartAnimation _levelStartAnimation;
  GameOverAnimation _gameOverAnimation;
  GameDoneAnimation _gameDoneAnimation;

  // The active animation, if any
  Animation *_activeAnimation;

  void drawScore();

public:
  int8_t numLives() { return _numLives; }
  void removeLive() { _numLives--; }
  uint8_t levelNum() { return _levelNum + 1; }
  uint16_t score() { return _score; }

  Level& level() { return _level; }
  void addToScore(uint8_t inc) { _score += inc; }

  bool registerLevelScore();
  bool registerGameScore();

  void signalDeath(const char* cause);
  void signalPickupCollected();
  void signalBoxDestroyed(Box& box);

  /* Starts a new game.
   */
  Animation* init(uint8_t initialLevel);

  /* Initiates Game Over animation
   */
  Animation* gameOver();

  /* Starts or re-starts the current level.
   */
  Animation* startLevel(bool restart);

  /* Starts next level.
   */
  Animation* nextLevel();

  void draw();
  void update();
};

extern Game game;

