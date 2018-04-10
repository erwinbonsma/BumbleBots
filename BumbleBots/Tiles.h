/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#ifndef __TILES_INCLUDED
#define __TILES_INCLUDED

#include "Utils.h"

#include "Movers.h"
#include "Waves.h"

struct TileType;

const int8_t TILEFLAG_ENEMY_ENTERING = 0x01;
const int8_t TILEFLAG_BOX_ENTERING = 0x02;

//-----------------------------------------------------------------------------
// Tile declaration

class Tile {
  friend class Tiles;

  /* The mover(s) at this unit, if any.
   *
   * Note: There can be multiple, as movers can form a linked list.
   */
  int8_t _moverIndex;

  // The object at this unit, if any.
  int8_t _objectIndex;

  int8_t _height0;

  // Height after applying wave
  int8_t _height;

  int8_t _flags;

  bool drawMovers(int8_t x, int8_t y) const;
  void drawMoversAndObjects(int8_t x, int8_t y) const;

public:
  Tile();

  void init(int8_t _height0);
  void reset();

  void setWave(int8_t waveHeight);
  int8_t height() const { return _height; }

  void setEnemyEntering() { _flags |= TILEFLAG_ENEMY_ENTERING; }
  void clearEnemyEntering() { _flags &= ~TILEFLAG_ENEMY_ENTERING; }
  bool isEnemyEntering() { return _flags & TILEFLAG_ENEMY_ENTERING; }

  void setBoxEntering() { _flags |= TILEFLAG_BOX_ENTERING; }
  void clearBoxEntering() { _flags &= ~TILEFLAG_BOX_ENTERING; }
  bool isBoxEntering() { return _flags & TILEFLAG_BOX_ENTERING; }

  void addMover(int8_t moverIndex);
  void removeMover(int8_t moverIndex);
  /* Returns the mover of the given type that resides at this tile, if any.
   * If excludeMover >= 0, it will not return a mover with this index.
   */
  int8_t moverOfType(MoverType moverType, int8_t excludeMover);
  bool containsMovers() { return _moverIndex >= 0; }

  void addObject(int8_t objectIndex);
  void removeObject(int8_t objectIndex);
  int8_t object() { return _objectIndex; }

  void draw(TilePos pos, TileType* tileType) const;
};

//-----------------------------------------------------------------------------
// TileSpec declaration

class TilesSpec {
public:
  /* Returns base height of tile at given position. This is the height without
   * a wave applied.
   */
  virtual int8_t baselineHeightAt(TilePos pos) const = 0;

  virtual TileType* tileTypeAt(TilePos pos) const = 0;
};

//-----------------------------------------------------------------------------
// Tiles declaration

class Tiles {
  const TilesSpec* _tilesSpec;

  // 1D-array of Tiles, representing a 2D map
  Tile _units[maxCols * maxRows];

  Tile _offMapTile;
  TilePos _offMapTilePos;

  ScreenPos _cameraPos;

  DirectionalWave _wave;
  uint8_t _waveStrength;
  int8_t _waveStrengthDelta;

  void drawPartOfIsoline(int8_t elementIndex);

public:
  Tiles();
  void init(const TilesSpec* tilesSpec, int8_t offMapTileHeight);
  void reset();

  ScreenPos cameraPos() const {
    return _cameraPos;
  }

  Tile& tileAtIndex(int8_t tileIndex);
  TilePos posOfTile(int8_t tileIndex) { return (TilePos)tileIndex; }

  /* Returns the index of the tile neighbouring the given on in the indicated
   * direction. It can return positions off the map. It is only valid when the 
   * provided tile index corresponds to a tile on the map.
   */
  int8_t neighbour(int8_t tileIndex, Heading heading);

  /* Adds mover to the map on the specified tile. This should only be called
   * once. I.e. it should not be called when the mover subsequently moves to
   * another tile.
   */
  void putMoverOnTile(int8_t moverIndex, int8_t tileIndex);

  /* Moves mover from its current tile to the specified tile.
   *
   * Note: The mover should be on a tile that is on the map.
   */
  void moveMoverToTile(int8_t moverIndex, int8_t tileIndex);

  /* Adds object to the map on the specified tile.
   */
  void putObjectOnTile(int8_t objectIndex, int8_t tileIndex);

  void attenuateWaves() { _waveStrengthDelta = -2; }

  void update();

  /* Draws the tiles. The player is passed to enable update of the camera
   * position based on the player position.
   */
  void draw(Player* player);
};

#endif
