/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Tiles.h"
#include "Movers.h"

//-----------------------------------------------------------------------------
// MenuTilesSpec declaration

class MenuTilesSpec : public TilesSpec {
  int8_t _maxLevelCompleted;
  int8_t _maxLevelUnlocked;

public:
  void init(int8_t maxLevelCompleted, int8_t maxLevelUnlocked);

  int8_t baselineHeightAt(TilePos pos) const;

  TileType* tileTypeAt(TilePos pos) const;
};

//-----------------------------------------------------------------------------
// LevelMenu declaration

class LevelMenu {
  MenuTilesSpec _tilesSpec;
  Player _player;

  void initPlayer();
  void addDigits();

public:
  void init();

  void update();
  void draw();
};

