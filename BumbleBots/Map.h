#include "Utils.h"

#include "Levels.h"
#include "Waves.h"

class Map;
class Mover;
class IsoLineElement;
struct TileType;

class MapUnit {
  // The mover at this unit, if any
  //Mover* _mover;

  int8_t _height0;

  // Height after applying wave
  int8_t _height;

public:
  MapUnit();

  void init(int8_t _height0);

  void setWave(int8_t waveHeight);
  int8_t height() const { return _height; }

  //void addMover(Mover* mover);
  //void removeMover(Mover* mover);

  void draw(MapPos pos, TileType* tileType) const;
};


class Map {
  const LevelDef* _levelDef;

  // 1D-array of MapUnits, representing a 2D map
  MapUnit _units[maxCols * maxRows];

  // 1D-array of IsoLineElement pointers
  //const uint8_t _numIsoLines;
  //IsoLineElement** _isoLines;

  DirectionalWave _wave;
  float _waveStrength;
  float _waveStrengthDelta;
public:
  Map();
  void init(const LevelDef* levelDef);

  uint8_t numCols() const {
    return _levelDef->mapDef.numCols;
  }

  uint8_t numRows() const {
    return _levelDef->mapDef.numRows;
  }

  //MapUnit const* unitAt(MapPos pos) const {
  //  return &_units[pos.col + pos.row * maxCols];
  //}

  void update();
  void draw();
};

