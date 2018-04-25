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

void ProgressTracker::init() {
  if (
    gb.save.get(SAVEINDEX_VMAJOR) != VMAJOR ||
    gb.save.get(SAVEINDEX_VMINOR) != VMINOR
  ) {
    // Data is stored in a different format, possibly not compatible.

    if (
      // v1.0 format stored incorrectly (as v0.1)
      gb.save.get(1) == 1 &&
      gb.save.get(0) == 0
    ) {
      for (uint8_t level = 0; level < 16; level++) {
        if (gb.save.get(SAVEINDEX_LEVELHI_L0 + level) != 0) {
          // Level score was incorrectly stored. No need to try to correct
          // this, as it is not yet used anyway. Only remember that level was
          // completed so that after upgrade, users will not notice a
          // difference
          gb.save.set(SAVEINDEX_LEVELHI_L0 + level, (int32_t)1);
        }
      }
    }
    else if (
      gb.save.get(SAVEINDEX_VMAJOR) == 1 &&
      gb.save.get(SAVEINDEX_VMINOR) == 0
    ) {
      gb.save.set(SAVEINDEX_MAXLEVELRUN, (int32_t)0);
    }
    else if (
      gb.save.get(SAVEINDEX_VMAJOR) != VMAJOR ||
      gb.save.get(SAVEINDEX_VMINOR) > VMINOR
    ) {
      // Reset all (incompatible) data to default
      for (uint8_t i = 2; i <= SAVEINDEX_LAST; i++) {
        gb.save.set(i, (int32_t)0);
      }
    }
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
    if (gb.save.get(SAVEINDEX_LEVELHI_L0 + level) > 0) {
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

uint16_t ProgressTracker::virtualHiScore() {
  uint16_t vscore = 0;

  for (uint8_t level = 0; level < numLevels; level++) {
    vscore += gb.save.get(SAVEINDEX_LEVELHI_L0 + level);
  }

  return vscore;
}

uint8_t ProgressTracker::maxLevelRun() {
  return gb.save.get(SAVEINDEX_MAXLEVELRUN);
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
