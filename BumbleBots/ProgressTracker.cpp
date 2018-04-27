/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "ProgressTracker.h"

#include "Levels.h"

//-----------------------------------------------------------------------------
// ProgressTracker implementation

const uint8_t VMAJOR = 1;
const uint8_t VMINOR = 1;

const uint8_t SAVEINDEX_VMAJOR = 0;
const uint8_t SAVEINDEX_VMINOR = 1;
const uint8_t SAVEINDEX_HISCORE = 2;
const uint8_t SAVEINDEX_MAXLEVELRUN = 3;
const uint8_t SAVEINDEX_LEVELHI_L0 = 4;
const uint8_t SAVEINDEX_LAST = SAVEINDEX_LEVELHI_L0 + 15;

void ProgressTracker::clearStoredHiScore() {
  gb.save.set(SAVEINDEX_HISCORE, (int32_t)0);
}

void ProgressTracker::clearStoredMaxLevelRun() {
  gb.save.set(SAVEINDEX_MAXLEVELRUN, (int32_t)0);
}

void ProgressTracker::clearStoredLevelScores(bool preserveCompletion) {
  for (uint8_t level = 0; level < 16; level++) {
    int32_t levelScore = (
      preserveCompletion &&
      gb.save.get(SAVEINDEX_LEVELHI_L0 + level) != 0
    ) ? 1 : 0;
    gb.save.set(SAVEINDEX_LEVELHI_L0 + level, levelScore);
  }
}

void ProgressTracker::init() {
  if (
    gb.save.get(SAVEINDEX_VMAJOR) != VMAJOR ||
    gb.save.get(SAVEINDEX_VMINOR) != VMINOR
  ) {
    // Reset all data. Although format itself has not changed, levels have been
    // tweaked so that previous scores are not valid anymore.
    clearStoredLevelScores(true);
    clearStoredHiScore();
    clearStoredMaxLevelRun();
  }

  dump();

  gb.save.set(SAVEINDEX_VMAJOR, (int32_t)VMAJOR);
  gb.save.set(SAVEINDEX_VMINOR, (int32_t)VMINOR);
}

void ProgressTracker::dump() {
#ifdef DEVELOPMENT
  SerialUSB.printf("Save file format v%d.%d\n", gb.save.get(SAVEINDEX_VMAJOR), gb.save.get(SAVEINDEX_VMINOR));
  SerialUSB.printf("High score = %d\n", gb.save.get(SAVEINDEX_HISCORE));
  SerialUSB.printf("Max level run = %d\n", gb.save.get(SAVEINDEX_MAXLEVELRUN));
  for (uint8_t i = 0; i < 16; i++) {
    SerialUSB.printf("Max score level %d = %d\n", (i + 1), gb.save.get(SAVEINDEX_LEVELHI_L0 + i));
  }
  SerialUSB.printf("Virtual high score = %d\n", virtualHiScore());
#endif
}

uint8_t ProgressTracker::maxStartLevel() {
  uint8_t skips = 1;
  uint8_t level = 0;

  while (level < numLevels - 1) {
    if (gb.save.get(SAVEINDEX_LEVELHI_L0 + level) == 0) {
      if (skips-- == 0) {
        // Not allowed to skip any more levels
        break;
      }
    }
    level++;
  }

  return level;
}

uint8_t ProgressTracker::numLevelsCompleted() {
  uint8_t numCompleted = 0;

  for (uint8_t level = 0; level < numLevels; level++) {
    if (didCompleteLevel(level)) {
      numCompleted++;
    }
  }

  return numCompleted;
}

uint16_t ProgressTracker::levelHiScore(uint8_t level) {
  return gb.save.get(SAVEINDEX_LEVELHI_L0 + level);
}

uint16_t ProgressTracker::hiScore() {
  return gb.save.get(SAVEINDEX_HISCORE);
}

uint8_t ProgressTracker::maxLevelRun() {
  return gb.save.get(SAVEINDEX_MAXLEVELRUN);
}

uint16_t ProgressTracker::virtualHiScore() {
  uint16_t vscore = 0;

  for (uint8_t level = 0; level < numLevels; level++) {
    uint16_t levelScore = levelHiScore(level);
    // Ignore 1-score levels which are only used to signal completion after
    // format change of stored data
    if (levelScore > 1) {
      vscore += levelScore;
    }
  }

  return vscore;
}

void ProgressTracker::startGame() {
  _score = 0;
  _levelRun = 0;
  _improvedFlags = 0;
}

void ProgressTracker::updateHiScore() {
  uint16_t oldHiScore = hiScore();

  if (_score > oldHiScore) {
    gb.save.set(SAVEINDEX_HISCORE, (int32_t)_score);
    _improvedFlags |= IMPROVED_HISCORE;
  }
}

bool ProgressTracker::levelDone(uint8_t level, uint16_t score) {
  uint16_t oldLevelHi = levelHiScore(level);
  uint16_t levelScore = score - _score;
  _score = score;

  if (levelScore > oldLevelHi) {
    gb.save.set(SAVEINDEX_LEVELHI_L0 + level, levelScore);
    _improvedFlags |= IMPROVED_VIRTUALHISCORE;
  }

  _levelRun++;
  if (_levelRun > maxLevelRun()) {
    gb.save.set(SAVEINDEX_MAXLEVELRUN, (int32_t)_levelRun);
    _improvedFlags |= IMPROVED_MAXLEVELRUN;
  }

  updateHiScore();

  return levelScore > oldLevelHi;
}

void ProgressTracker::gameDone(uint16_t finalScore) {
  _score = finalScore;

  updateHiScore();
}

ProgressTracker progressTracker;
