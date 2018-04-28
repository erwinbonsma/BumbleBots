/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

//-----------------------------------------------------------------------------
// ProgressTracker declaration

const int8_t IMPROVED_HISCORE = 0x01;
const int8_t IMPROVED_MAXLEVELRUN = 0x02;
const int8_t IMPROVED_VIRTUALHISCORE = 0x04;
const int8_t PLAYER_DIED_THIS_LEVEL = 0x08;

class ProgressTracker {
  uint8_t _flags;
  uint8_t _levelRun;
  // Updated at the end of each level so that it can be used to determine the
  // level score.
  uint16_t _score;

  void dump();
  void updateHiScore();

  void clearStoredHiScore();
  void clearStoredMaxLevelRun();
  void clearStoredLevelScores(bool preserveCompletion);

public:
  void init();

  // The maximum starting level, given current progress
  uint8_t maxStartLevel();

  // The number of levels completed
  uint8_t numLevelsCompleted();
  bool didCompleteLevel(uint8_t levelIndex) { return levelHiScore(levelIndex) > 0; }

  uint8_t firstUncompletedLevel();

  uint16_t score() { return _score; }

  uint16_t levelHiScore(uint8_t levelIndex);
  uint16_t hiScore();
  bool improvedHiScore() { return _flags & IMPROVED_HISCORE; }

  // The hiscore if the best score for each level would be reached in the same game.
  uint16_t virtualHiScore();
  bool improvedVirtualHiScore() { return _flags & IMPROVED_VIRTUALHISCORE; }

  uint8_t levelRun() { return _levelRun; }
  uint8_t maxLevelRun();
  bool improvedMaxLevelRun() { return _flags & IMPROVED_MAXLEVELRUN; }

  void signalPlayerDeath() { _flags |= PLAYER_DIED_THIS_LEVEL; }
  bool playerDiedThisLevel() { return _flags & PLAYER_DIED_THIS_LEVEL; }

  // Returns true iff this is a new level hi
  bool levelDone(uint8_t levelIndex, uint16_t totalScore);

  void startGame();
  void gameDone(uint16_t finalScore);
};

extern ProgressTracker progressTracker;
