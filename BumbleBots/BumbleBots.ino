#include <Gamebuino-Meta.h>

#include "Game.h"
//#include "Globals.h"

bool _slowMotionEnabled = false;
uint8_t _slowMotionCount = 0;

void slowMotion(bool enable) {
  _slowMotionEnabled = enable;
  _slowMotionCount = 0;

  gb.setFrameRate(_slowMotionEnabled ? 1 : 25);
}

void signalDeath(const char* causeOfDeath) {
  game.signalDeath(causeOfDeath);
}

void signalPickupCollected() {
  game.signalPickupCollected();
}

void setup() {
  gb.begin();

  gb.setFrameRate(25);

  game.init();
}

void loop() {
  while(!gb.update());
  gb.display.clear();
  gb.lights.clear();

//  if (gb.buttons.held(BUTTON_A, 0)) {
//    slowMotion(true);
//  }
//  if (gb.buttons.held(BUTTON_B, 0)) {
//    slowMotion(false);
//  }

  if (1) {
    if (!_slowMotionEnabled || _slowMotionCount++ >= 2) {
      _slowMotionCount = 0;

      game.update();
    }
    game.draw();
  }

  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(1, 58);
  gb.display.printf("%d", cpuLoad);
}
