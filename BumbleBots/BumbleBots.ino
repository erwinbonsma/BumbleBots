#include <Gamebuino-Meta.h>

#include "Levels.h"
#include "Animations.h"

uint8_t levelNum = 0;
Level level = Level();

uint8_t frameRate = 25;

DieAnimation dieAnimation;
LevelDoneAnimation levelDoneAnimation;

// The active animation, if any
Animation *animation = 0;

const char *deathCause = 0;

void signalDeath(const char* cause) {
  deathCause = cause;
}

void signalPickupCollected() {
  level.pickupCollected();

  if (level.isCompleted()) {
    levelDoneAnimation.init();
    animation = &levelDoneAnimation;
  }
}

void nextLevel() {
  levelNum = (levelNum + 1 ) % numLevels;
  level.init(&levelSpecs[levelNum]);
}

void setup() {
  gb.begin();

  level.init(&levelSpecs[levelNum]);

  gb.setFrameRate(frameRate);
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  if (gb.buttons.held(BUTTON_A, 0)) {
    level.reset();
    //if (frameRate > 1) {
    //  gb.setFrameRate(--frameRate);
    //}
  }
  if (gb.buttons.held(BUTTON_B, 0)) {
    nextLevel();
    //gb.setFrameRate(++frameRate);
  }

  if (1) {
    if (animation) {
      animation = animation->update();
    }

    deathCause = 0;
    level.update();
    if (!animation && deathCause) {
      dieAnimation.init(deathCause);
      animation = &dieAnimation;
    }

    level.draw();
    if (animation) {
      animation->draw();
    }
  }

  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.printf("%d/%d", cpuLoad, frameRate);
}
