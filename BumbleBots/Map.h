#include "Utils.h"

class Map;
class Wave;
class Mover;
class IsoLineElement;

class MapUnit {
  Map* _map;

  // The mover at this unit, if any
  Mover* _mover;

  MapPos _pos;

  // Intrinsic height
  float _height0;

  // Height after applying wave
  float _height;

  // Previous height value
  float _prevHeight;

  float _waveFlexibility;

public:
  MapUnit();
  void init(Map* map, MapPos pos, float height0);

  void setWave(float waveHeight);
  float height() const { return _height; }

  void addMover(Mover* mover);
  void removeMover(Mover* mover);

  MapUnit* const neighbour(Heading heading);

  void draw() const;
};

class Map {
  const uint8_t _numCols;
  const uint8_t _numRows;

  // 1D-array of MapUnits, representing a 2D map
  MapUnit* _units;

  // 1D-array of IsoLineElement pointers
  const uint8_t _numIsoLines;
  IsoLineElement** _isoLines;

  Wave* _wave;
  float _waveStrength;
  float _waveStrengthDelta;

public:
  Map(uint8_t numCols, uint8_t numRows);
  ~Map();

  uint8_t numCols() const { return _numCols; }
  uint8_t numRows() const { return _numRows; }

  MapUnit* unitAt(MapPos pos) const { return &_units[pos.col * _numRows + pos.row]; }

  void update();
  void draw();
};

