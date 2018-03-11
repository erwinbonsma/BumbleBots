#include "Utils.h"

#include "Levels.h"
#include "Waves.h"

class Tiles;
class Mover;
class IsoLineElement;
struct TileType;

class Tile {
  friend class Tiles;

  // The mover at this unit, if any
  uint8_t _moverIndex;

  int8_t _height0;

  // Height after applying wave
  int8_t _height;

public:
  Tile();

  void init(int8_t _height0);

  void setWave(int8_t waveHeight);
  int8_t height() const { return _height; }

  void draw(TilePos pos, TileType* tileType) const;
};


class Tiles {
  const LevelSpec* _levelSpec;

  // 1D-array of Tiles, representing a 2D map
  Tile _units[maxCols * maxRows];

  // 1D-array of IsoLineElement pointers
  //const uint8_t _numIsoLines;
  //IsoLineElement** _isoLines;

  DirectionalWave _wave;
  float _waveStrength;
  float _waveStrengthDelta;
public:
  Tiles();
  void init(const LevelSpec* levelSpec);

  uint8_t numCols() const {
    return _levelSpec->tilesSpec.numCols;
  }

  uint8_t numRows() const {
    return _levelSpec->tilesSpec.numRows;
  }

  /* Adds mover to specified tile for drawing purposes.
   * This implicitly removes it from current tile, if any
   */
  void addMover(uint8_t tileIndex, uint8_t moverIndex);

  void update();
  void draw();
};

