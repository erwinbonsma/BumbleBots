#include "Map.h"

#include <assert.h>

// Empty constructor to enable usage in array.
// Entries should be initialized using init() method before usage.
MapUnit::MapUnit() {
  _map = 0;
}

void MapUnit::init(Map* map, MapPos pos, float height0) {
  assert(!_map);

  _map = map;
  _pos = pos;

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
  MapPos pos;
  pos.col = _pos.col + colDelta[(int)heading];
  pos.row = _pos.row + rowDelta[(int)heading];

  if (pos.col < _map->numCols() && pos.row < _map->numRows()) {
    return _map->unitAt(pos);
  }
  else {
    return 0;
  }
}

Map::Map(uint8_t numCols, uint8_t numRows) {
  _numCols = numCols + 2;
  _numRows = numRows + 2;

  _units = (MapUnit*) malloc(_numCols * _numRows * sizeof(MapUnit));
  MapPos pos;
  for (pos.col = 0; pos.col < _numCols; pos.col++) {
    for (pos.row = 0; pos.row < _numRows; pos.row++) {
      float height0 = 0;
      if (
        pos.col == 0 || pos.col == _numCols - 1 ||
        pos.row == 0 || pos.row == _numRows - 1
      ) {
        height0 = -10;
      }
      _units[pos.col * _numRows + pos.row].init(this, pos, height0);
    }
  }
}

Map::~Map() {
  free(_units);
}


