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
const uint8_t VMINOR = 0;

const uint8_t SAVEINDEX_VMAJOR = 1;
const uint8_t SAVEINDEX_VMINOR = 0;
const uint8_t SAVEINDEX_HISCORE = 2;
const uint8_t SAVEINDEX_MAXLEVELRUN = 3;
const uint8_t SAVEINDEX_LEVELHI_L0 = 4;
const uint8_t SAVEINDEX_LAST = SAVEINDEX_LEVELHI_L0 + 15;

const SaveDefault saveDefaults[] = {
  { SAVEINDEX_VMAJOR, SAVETYPE_INT, 1, 0 },
  // Minor version
  { SAVEINDEX_VMINOR, SAVETYPE_INT, 0, 0 },
  // Hi-score
  { SAVEINDEX_HISCORE, SAVETYPE_INT, 0, 0 },
  // Max level run
  { SAVEINDEX_MAXLEVELRUN, SAVETYPE_INT, 0, 0 },
  // Max level score, Level 1..16
  { SAVEINDEX_LEVELHI_L0, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 1, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 2, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 3, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 4, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 5, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 6, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 7, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 8, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 9, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 10, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 11, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 12, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 13, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 14, SAVETYPE_INT, 0, 0 },
  { SAVEINDEX_LEVELHI_L0 + 15, SAVETYPE_INT, 0, 0 },
};

void ProgressTracker::init() {
  gb.save.config(saveDefaults);

  if (
    gb.save.get(SAVEINDEX_VMAJOR) != VMAJOR ||
    gb.save.get(SAVEINDEX_VMINOR) > VMINOR
  ) {
    // Reset incompatible data
    for (uint8_t i = 2; i <= SAVEINDEX_LAST; i++) {
      gb.save.set(i, (int32_t)0);
    }
  }

  gb.save.set(SAVEINDEX_VMAJOR, (int32_t)VMAJOR);
  gb.save.set(SAVEINDEX_VMINOR, (int32_t)VMINOR);
}

uint8_t ProgressTracker::maxStartLevel() {
  uint8_t skips = 1;
  uint8_t level = 0;

  while (level < numLevels - 1) {
    if (gb.save.get(SAVEINDEX_LEVELHI_L0 + level) == 0) {
      if (skips-- == 0) {
        // Not allowed to skip anymore levels
        break;
      }
    }
    level++;
  }

  return level;
}

uint16_t ProgressTracker::levelHiScore(uint8_t level) {
  return gb.save.get(SAVEINDEX_LEVELHI_L0 + level);
}

uint16_t ProgressTracker::hiScore() {
  return gb.save.get(SAVEINDEX_HISCORE);
}

uint16_t ProgressTracker::virtualHiScore() {
  uint16_t vscore = 0;

  for (uint8_t level = 0; level < numLevels; level++) {
    vscore += gb.save.get(SAVEINDEX_LEVELHI_L0 + level);
  }

  return vscore;
}

bool ProgressTracker::levelDone(uint8_t level, uint16_t levelScore) {
  uint16_t oldHi = gb.save.get(SAVEINDEX_LEVELHI_L0 + level);

  if (levelScore > oldHi) {
    gb.save.set(SAVEINDEX_LEVELHI_L0 + level, levelScore);
    return true;
  }

  return false;
}

bool ProgressTracker::gameDone(uint8_t levelRun, uint16_t finalScore) {
  uint8_t oldRun = gb.save.get(SAVEINDEX_MAXLEVELRUN);
  if (levelRun > oldRun) {
    gb.save.set(SAVEINDEX_MAXLEVELRUN, (int32_t)levelRun);
  }

  uint16_t oldHi = gb.save.get(SAVEINDEX_HISCORE);
  if (finalScore > oldHi) {
    gb.save.set(SAVEINDEX_HISCORE, (int32_t)finalScore);
    return true;
  }

  return false;
}

ProgressTracker progressTracker;
