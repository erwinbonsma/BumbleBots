#include "Map.h"

#include <assert.h>

// Empty constructor to enable usage in array.
// Entries should be initialized using init() method before usage.
MapUnit::MapUnit() {
  _map = 0;
}

void MapUnit::init(Map* map, uint8_t col, uint8_t row, float height0) {
  assert(!_map);

  _map = map;
  _col = col;
  _row = row;

  _height0 = height0;
  _height = 0;
  _mover = 0;
  _waveFlexibility = 1;
}

void MapUnit::setWave(float waveHeight) {
  _prevHeight = _height;
  _height = _height0 + _waveFlexibility * waveHeight;
}

void MapUnit::addMover(Mover* mover) {
  if (mover->drawUnit) {
    mover->drawUnit->removeMover(mover);
  }
  mover->drawUnit = this;
  // TODO: Update when supporting multiple movers on one tile
  _mover = mover;
}

void MapUnit::removeMover(Mover* mover) {
  assert(_mover == mover);
  assert(mover->drawUnit == this);
  mover->drawUnit = 0;
  // TODO: Update when supporting multiple movers on one tile
  _mover = 0;
}

MapUnit* const MapUnit::neighbour(Heading heading) {
  uint8_t c = _col + colDelta[(int)heading];
  uint8_t r = _row + rowDelta[(int)heading];

  if (c < _map->numCols() && r < _map->numRows()) {
    return _map->unitAt(c, r);
  }
  else {
    return 0;
  }
}

Map::Map(uint8_t numCols, uint8_t numRows) {
  _numCols = numCols + 2;
  _numRows = numRows + 2;

  _units = (MapUnit*) malloc(_numCols * _numRows * sizeof(MapUnit));
  for (uint8_t c = 0; c < _numCols; c++) {
    for (uint8_t r = 0; r < _numRows; r++) {
      float height0 = 0;
      if (
        c == 0 || c == _numCols - 1 ||
        r == 0 || r == _numRows - 1
      ) {
        height0 = -10;
      }
      _units[c * _numRows + r].init(this, c, r, height0);
    }
  }
}

Map::~Map() {
  free(_units);
}


