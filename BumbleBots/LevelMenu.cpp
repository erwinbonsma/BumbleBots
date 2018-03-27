/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "LevelMenu.h"

#include "Utils.h"
#include "Globals.h"
#include "TileTypes.h"

//const uint8_t zeroDigitTop = {
//  // Zero, top
//  { 17, 3, 9, 7, 7, 1, 3, 4, 4, 4, 2, 1, 2},
//  // Zero, bottom
//  { 3, 3, 2, 4, 5, 4, 4, 3, 4, 4, 1, 4, 6, 5, 6, 1, 5 },
//  // One, top
//  { 29, 7, 7, 5, 6, 1, 9 },
//  // One, bottom
//  { 12, 3, 2, 3, 1, 4, 7, 5, 10, 4, 7, 1, 5}
//}

//-----------------------------------------------------------------------------
// MenuTilesSpec implementation

int8_t MenuTilesSpec::levelAt(TilePos pos) const {
  assertTrue(isPosOnMap(pos));

  int8_t digitCol = colOfPos(pos) / 2;
  int8_t digitRow = rowOfPos(pos) / 2;

  return 15 - digitCol - 4 * digitRow;
}

void MenuTilesSpec::init(int8_t maxLevelCompleted, int8_t maxLevelUnlocked) {
  _maxLevelCompleted = maxLevelCompleted;
  _maxLevelUnlocked = maxLevelUnlocked;
}

int8_t MenuTilesSpec::baselineHeightAt(TilePos pos) const {
  return levelAt(pos) <= _maxLevelUnlocked ? 0 : 4;
}

TileType* MenuTilesSpec::tileTypeAt(TilePos pos) const {
  return &tileTypes[0];
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
  // TODO
}

void LevelMenu::init() {
  _tilesSpec.init(2, 4); // TODO: Use actual values
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

