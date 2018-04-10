/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "LevelMenu.h"

#include "Utils.h"
#include "Globals.h"
#include "Levels.h"
#include "TileTypes.h"
#include "Palettes.h"
#include "ProgressTracker.h"

int8_t levelAt(TilePos pos) {
  assertTrue(isPosOnMap(pos));

  int8_t digitCol = colOfPos(pos) / 2;
  int8_t digitRow = rowOfPos(pos) / 2;

  return 15 - digitCol - 4 * digitRow;
}

//-----------------------------------------------------------------------------
// MenuTilesSpec implementation

void MenuTilesSpec::init(int8_t maxLevelUnlocked) {
  _maxLevelUnlocked = maxLevelUnlocked;
}

int8_t MenuTilesSpec::baselineHeightAt(TilePos pos) const {
  return levelAt(pos) <= _maxLevelUnlocked ? 0 : 4;
}

uint8_t MenuTilesSpec::tileTypeIndexAt(TilePos pos) const {
  int8_t level = levelAt(pos);
  return (level + level / 4) % 2 ? TILETYPE_MENU1 : TILETYPE_MENU2;
}

TileType* MenuTilesSpec::tileTypeAt(TilePos pos) const {
  return &tileTypes[tileTypeIndexAt(pos)];
}

//-----------------------------------------------------------------------------
// LevelMenu implementation

void LevelMenu::initPlayer() {
  numMovers = 0;
  _player.init(numMovers++);
  _player.reset();
  movers[_player.index()] = &_player;
  tiles.putMoverOnTile(_player.index(), makeTilePos(6, 6));
}

void LevelMenu::addDigits() {
  numObjects = 0;
  for (TilePos pos = maxTilePos; --pos >= 0; ) {
    uint8_t level = levelAt(pos);
    bool topPart = (rowOfPos(pos) % 2) == 0;
    int8_t digit = (colOfPos(pos) % 2) == 0 ? (level + 1) / 10 : (level + 1) % 10;
    ColorIndex digitColor =
      !progressTracker.levelCompleted(level)
      ? INDEX_DARKGRAY
      : (_tilesSpec.tileTypeIndexAt(pos) == TILETYPE_MENU1)
        ? INDEX_PINK
        : INDEX_LIGHTGREEN;

    int8_t i = numObjects++;
    _digitsParts[i].init(i, digit, topPart, digitColor);
    objects[i] = &_digitsParts[i];

    tiles.putObjectOnTile(i, pos);
  }
}

void LevelMenu::drawTitle() {
  const char* title = levelSpecs[levelAt(_player.tilePos())].title;
  uint8_t w = gb.display.getFontWidth() * strlen(title);

  gb.display.setColor(INDEX_BLUE);
  gb.display.fillRoundRect(40 - w/2 - 2, 0, w + 3, gb.display.getFontHeight() + 2, 1);

  gb.display.setColor(INDEX_WHITE);
  gb.display.setCursor(40 - w/2, 1);
  gb.display.print(title);
}

void LevelMenu::init() {
  _tilesSpec.init(progressTracker.maxStartLevel());
  tiles.init(&_tilesSpec, 16);
  tiles.reset();

  // Create and add player
  initPlayer();

  // Add digits
  addDigits();
}

void LevelMenu::update() {
  _player.update();

  if (gb.buttons.held(BUTTON_A, 0)) {
    startGameAtLevel(levelAt(_player.tilePos()));
  }
}

void LevelMenu::draw() {
  tiles.draw(&_player);

  drawTitle();
}
