/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Game.h"
#include "LevelMenu.h"
#include "ProgressTracker.h"

bool _slowMotionEnabled = false;
uint8_t _slowMotionCount = 0;

void toggleSlowMotion() {
  _slowMotionEnabled = !_slowMotionEnabled;
  _slowMotionCount = 0;

  gb.setFrameRate(_slowMotionEnabled ? 1 : 25);
}

void checkSlowMotionButtons() {
  if (gb.buttons.held(BUTTON_B, 0)) {
    toggleSlowMotion();
  }
}

void displayCpuLoad() {
  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(1, 58);
  gb.display.printf("%d", cpuLoad);
  if (_slowMotionEnabled) {
    gb.display.printf(" SM");
  }
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

  progressTracker.init();

  showLevelMenu();
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  gb.lights.clear();

#ifdef DEVELOPMENT
  checkSlowMotionButtons();
#endif

  if (gb.buttons.held(BUTTON_MENU, 0) && loopHandler != &levelMenu) {
    showLevelMenu();
  }

  if (!_slowMotionEnabled || _slowMotionCount++ >= 2) {
    _slowMotionCount = 0;

    loopHandler->update();
  }
  loopHandler->draw();

#ifdef DEVELOPMENT
  displayCpuLoad();
#endif
}
