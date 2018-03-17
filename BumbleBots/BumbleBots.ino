#include <Gamebuino-Meta.h>

#include "Levels.h"

uint8_t levelNum = 0;
Level level = Level();

uint8_t frameRate = 20;

void setup() {
  gb.begin();

  level.init(&levelSpecs[levelNum]);
  level.reset();

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
    levelNum = (levelNum + 1 ) % numLevels;
    level.init(&levelSpecs[levelNum]);
    level.reset();
    //gb.setFrameRate(++frameRate);
  }

  level.update();
  level.draw();

  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.printf("%d/%d", cpuLoad, frameRate);
}
