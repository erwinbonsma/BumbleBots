/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "StatsScreen.h"

#include "Globals.h"
#include "Images.h"
#include "ProgressTracker.h"

void drawScreen(int8_t x0, int8_t y0, int8_t w, int8_t h) {
  gb.display.setColor(INDEX_BLACK);
  gb.display.drawRect(x0, y0, w, h);

  gb.display.setColor(INDEX_WHITE);
  gb.display.drawRect(x0, y0, w-1, h-1);

  gb.display.setColor(INDEX_GRAY);
  gb.display.drawRect(x0+1, y0+1, w-2, h-2);
}

void StatsScreen::init(uint8_t levelRun, uint16_t score) {
  _levelRun = levelRun;
  _score = score;
}

void StatsScreen::update() {
  if (gb.buttons.held(BUTTON_A, 0)) {
    showLevelMenu();
  }
}

void StatsScreen::draw() {
  gb.display.setColor(INDEX_GREEN);

  gb.display.setCursor(23 + 3*4, 3);
  gb.display.printf("score:");
  gb.display.setCursorX(58);
  gb.display.printf("%5d", _score);

  gb.display.setCursor(23, 9);
  gb.display.printf("hi-score:");
  gb.display.setCursorX(58);
  gb.display.printf("%5d", progressTracker.hiScore());

  gb.display.setCursor(23, 15);
  gb.display.printf("vi-score:");
  gb.display.setCursorX(58);
  gb.display.printf("%5d", progressTracker.virtualHiScore());

  gb.display.setCursor(3 + 4*4, 23);
  gb.display.printf("level run:");
  gb.display.setCursorX(70);
  gb.display.printf("%2d", _levelRun);

  gb.display.setCursor(3, 29);
  gb.display.printf("max level run:");
  gb.display.setCursorX(70);
  gb.display.printf("%2d", progressTracker.maxLevelRun());

  gb.display.setCursor(11, 37);
  gb.display.printf("levels done:");
  gb.display.setCursorX(70);
  gb.display.printf("%2d", progressTracker.numLevelsCompleted());

  drawScreen(0, 0, 80, 45);

  gb.display.setColor(INDEX_DARKGRAY);
  gb.display.fillRect(0, 45, 80, 19);

  gb.display.drawImage(54, 41, botMediumImage);
}
