/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Game.h"
#include "LevelMenu.h"

bool _slowMotionEnabled = false;
uint8_t _slowMotionCount = 0;

void slowMotion(bool enable) {
  _slowMotionEnabled = enable;
  _slowMotionCount = 0;

  gb.setFrameRate(_slowMotionEnabled ? 1 : 25);
}

void checkSlowMotionButtons() {
  if (gb.buttons.held(BUTTON_A, 0)) {
    slowMotion(true);
  }
  if (gb.buttons.held(BUTTON_B, 0)) {
    slowMotion(false);
  }
}

void displayCpuLoad() {
  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(1, 58);
  gb.display.printf("%d", cpuLoad);
}

void signalDeath(const char* causeOfDeath) {
  game.signalDeath(causeOfDeath);
}

void signalPickupCollected() {
  game.signalPickupCollected();
}

LevelMenu levelMenu;
LoopHandler* loopHandler;

void showLevelMenu() {
  levelMenu.init();
  loopHandler = &levelMenu;
}

void startGameAtLevel(uint8_t levelNum) {
  game.init(levelNum);
  loopHandler = &game;
}

void setup() {
  gb.begin();

  gb.setFrameRate(25);

  showLevelMenu();
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  gb.lights.clear();

  //checkSlowMotionButtons();

  if (!_slowMotionEnabled || _slowMotionCount++ >= 2) {
    _slowMotionCount = 0;

    loopHandler->update();
  }
  loopHandler->draw();

  displayCpuLoad();
}
