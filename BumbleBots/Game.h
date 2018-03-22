#include "Levels.h"
#include "Animations.h"

class Game {
  int8_t _numLives;
  int8_t _levelNum;
  int16_t _score;
  int16_t _displayScore;

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
  int8_t levelNum() { return _levelNum + 1; }
  Level* level() { return &_level; }
  void addToScore(uint8_t inc) { _score += inc; }

  void signalDeath(const char* cause);
  void signalPickupCollected();

  /* Starts a new game.
   */
  Animation* init();

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

