#include "Movers.h"
#include "Utils.h"

class Map;

class MapUnit {
  Map* _map;

  // The mover at this unit, if any
  Mover* _mover;

  uint8_t _col;
  uint8_t _row;

  // Intrinsic height
  float _height0;

  // Height after applying wave
  float _height;

  // Previous height value
  float _prevHeight;

  float _waveFlexibility;

public:
  MapUnit();
  void init(Map* map, uint8_t col, uint8_t row, float height0);

  void setWave(float waveHeight);

  void addMover(Mover* mover);
  void removeMover(Mover* mover);

  MapUnit* const neighbour(Heading heading);
};


class Map {
  uint8_t _numCols;
  uint8_t _numRows;

  // 1D-array of MapUnits, representing a 2D map
  MapUnit* _units;

public:
  Map(uint8_t numCols, uint8_t numRows);
  ~Map();

  uint8_t const numCols() { return _numCols; }
  uint8_t const numRows() { return _numRows; }

  MapUnit* const unitAt(uint8_t col, uint8_t row) { return &_units[col * _numRows + row]; }

  void update();
  void draw(int16_t cameraX, int16_t cameraY);
};

