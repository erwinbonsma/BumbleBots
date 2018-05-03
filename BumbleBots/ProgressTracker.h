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
const int8_t LEVEL_RESUMED = 0x08;

class ProgressTracker {
  uint8_t _flags;
  uint8_t _levelRun;
  // Updated at the end of each level so that it can be used to determine the
  // level score.
  uint16_t _score;

  void dump();

  void clearStoredHiScore();
  void clearStoredMaxLevelRun();
  void clearStoredLevelScores(bool preserveCompletion);

  void clearLevelResumed() { _flags &= ~LEVEL_RESUMED; }
  void setLevelResumed() { _flags |= LEVEL_RESUMED; }
  bool levelResumed() { return _flags & LEVEL_RESUMED; }

  void updateHiScore();

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

  void startGame();

  /* Invoke to signal when player starts level and this attempt should be
   * considered for hi-score. This is the case when the level is started in its
   * initial state.
   */
  void startLevel(uint16_t totalScore);

  /* Invoke when a player died and resumes the level and the level is not
   * restored to its original state. If the level is completed, it will not be
   * considered for a level hi-score.
   */
  void resumeLevel();

  /* Invoke to signal that a level has been completed. This will update stored
   * progress if needed.
   *
   * Returns true iff this is a new level hi.
   */
  bool levelDone(uint8_t levelIndex, uint16_t totalScore);

  /* Invoke to signal that the game is done. This will update stored progress
   * if needed.
   *
   * Returns true iff this is a new hi-score
   */
  bool gameDone(uint16_t finalScore);
};

extern ProgressTracker progressTracker;
