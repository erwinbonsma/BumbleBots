/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "StatsScreen.h"

#include "Globals.h"
#include "Images.h"
#include "ProgressTracker.h"

void drawScreen() {
  int8_t x0 = 0;
  int8_t y0 = 0;
  int8_t w = 80;
  int8_t h = 45;
  int8_t bottomH = 10;

  gb.display.setColor(INDEX_BLACK);
  gb.display.drawRect(x0, y0, w, h);

  gb.display.setColor(INDEX_GRAY);
  gb.display.drawRect(x0, y0, w - 1, h - 1);

  gb.display.setColor(INDEX_DARKGRAY);
  gb.display.drawRect(x0 + 1, y0 + 1, w - 2, h - 2);
  gb.display.fillRect(x0 + 1, h - bottomH, w - 2, bottomH - 1);
}

void drawLevelProgress() {
  gb.display.setColor(INDEX_GRAY);
  gb.display.drawRect(5, 37, 70, 5);

  gb.display.setColor(INDEX_BLACK);
  gb.display.drawRect(5, 37, 69, 4);

  int8_t maxStartLevel = progressTracker.maxStartLevel();
  int8_t y = 38;
  for (uint8_t level = 0; level <= 16; level++) {
    uint16_t score = level < 16 ? progressTracker.levelHiScore(level) : 0;
    int8_t x = 6 + level * 4;

    for (uint8_t bit = 0; bit < 9; bit++) {
      bool isHi = (bit + score) % 2;
      if (level < maxStartLevel) {
        gb.display.setColor(isHi ? INDEX_LIGHTGREEN : INDEX_GREEN);
      } else {
        gb.display.setColor(isHi ? INDEX_RED : INDEX_PURPLE);
      }
      gb.display.drawPixel(x + bit % 3, y + bit / 3);
      score = score / 2;
    }
    gb.display.setColor(level < maxStartLevel ? INDEX_GREEN : INDEX_PURPLE);
    gb.display.drawFastVLine(x + 3, y, 3);
  }
}

void StatsScreen::init(uint8_t levelRun, uint16_t score) {
  _levelRun = levelRun;
  _score = score;
  _animCount = 0;
}

void StatsScreen::update() {
  _animCount++;

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

  gb.display.setColor(INDEX_DARKGRAY);
  gb.display.fillRect(0, 46, 80, 19);

  drawScreen();
  drawLevelProgress();

  int16_t dx = 0;
  int16_t dy = 0;
  if (_animCount < 80) {
    dx = 40 - _animCount / 2;
    dy = 20 - (int16_t)_animCount / 4;
  }
  gb.display.drawImage(54 + dx, 41 + dy, botMediumImage);
}
