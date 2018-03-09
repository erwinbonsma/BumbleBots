#include "Movers.h"
#include "Utils.h"

struct MapPos {
  uint8_t col;
  uint8_t row;
};

class Map;

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

  MapUnit* const unitAt(MapPos pos) { return &_units[pos.col * _numRows + pos.row]; }

  void update();
  void draw(int16_t cameraX, int16_t cameraY);
};

