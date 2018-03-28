/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "LevelMenu.h"

#include "Utils.h"
#include "Globals.h"
#include "TileTypes.h"
#include "Palettes.h"

int8_t levelAt(TilePos pos) {
  assertTrue(isPosOnMap(pos));

  int8_t digitCol = colOfPos(pos) / 2;
  int8_t digitRow = rowOfPos(pos) / 2;

  return 15 - digitCol - 4 * digitRow;
}

//-----------------------------------------------------------------------------
// MenuTilesSpec implementation

void MenuTilesSpec::init(int8_t maxLevelCompleted, int8_t maxLevelUnlocked) {
  _maxLevelCompleted = maxLevelCompleted;
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
  tiles->putMoverOnTile(_player.index(), makeTilePos(6, 6));
}

void LevelMenu::addDigits() {
  numObjects = 0;
  for (TilePos pos = maxTilePos; --pos >= 0; ) {
    uint8_t level = levelAt(pos);
    bool topPart = (rowOfPos(pos) % 2) == 0;
    int8_t digit = (colOfPos(pos) % 2) == 0 ? level / 10 : level % 10;
    ColorIndex digitColor =
      (level > _tilesSpec.maxLevelCompleted())
      ? INDEX_GRAY
      : (_tilesSpec.tileTypeIndexAt(pos) == TILETYPE_MENU1)
        ? INDEX_PINK
        : INDEX_LIGHTGREEN;

    int8_t i = numObjects++;
    _digitsParts[i].init(i, digit, topPart, digitColor);
    objects[i] = &_digitsParts[i];

    if (1) {
      tiles->putObjectOnTile(i, pos);
    }
  }
}

void LevelMenu::init() {
  _tilesSpec.init(8, 10); // TODO: Use actual values
  tiles->init(&_tilesSpec, 16);
  tiles->reset();

  // Create and add player
  initPlayer();

  // Add digits
  addDigits();
}

void LevelMenu::update() {
  _player.update();
}

void LevelMenu::draw() {
  tiles->draw(&_player);

  // TO DO: Show selected level
}

