/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

//-----------------------------------------------------------------------------
// ProgressTracker declaration

class ProgressTracker {
public:
  void init();

  // The maximum starting level, given current progress
  uint8_t maxStartLevel();

  uint16_t levelHiScore(uint8_t levelIndex);
  bool levelCompleted(uint8_t levelIndex) { return levelHiScore(levelIndex) > 0; }
  uint16_t hiScore();

  // The hiscore if the best score for each level was reached in the same game.
  uint16_t virtualHiScore();

  uint8_t maxLevelRun();

  // Returns true iff this is a new level hi
  bool levelDone(uint8_t levelIndex, uint16_t levelScore);

  void gameDone(uint8_t levelRun, uint16_t finalScore);
};

extern ProgressTracker progressTracker;
