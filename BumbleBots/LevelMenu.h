/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Tiles.h"
#include "Movers.h"
#include "Objects.h"

//-----------------------------------------------------------------------------
// MenuTilesSpec declaration

class MenuTilesSpec : public TilesSpec {
  int8_t _maxLevelUnlocked;

public:
  void init(int8_t maxLevelUnlocked);

  int8_t baselineHeightAt(TilePos pos) const;

  uint8_t tileTypeIndexAt(TilePos pos) const;
  TileType& tileTypeAt(TilePos pos) const;
};

//-----------------------------------------------------------------------------
// LevelMenu declaration

class LevelMenu : public LoopHandler {
  MenuTilesSpec _tilesSpec;
  Player _player;
  MenuDigit _digitsParts[maxTiles];

  void initPlayer();
  void addDigits();
  void drawTitle();

public:
  void init();

  void update();
  void draw();
};

