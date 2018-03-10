#include "Map.h"

#include "Waves.h"
#include "Movers.h"
#include "ImageData.h"
#include "TileTypes.h"

#include <assert.h>

enum IsoLineSide {
  LEFT_SIDE = 0,
  RIGHT_SIDE = 1
};

//-----------------------------------------------------------------------------
// IsoLine declaration

class IsoLine {
  const Map* _map;
  const MapPos _startPos;
  const uint8_t _length;

public:
  IsoLine(Map* map, MapPos start);

  uint8_t length() { return _length; }
  MapUnit* unitAt(uint8_t index) const;
};

//------------------------------------------------------------------------------
// IsoLineElement declaration

class IsoLineElement {
public:
  virtual float height(IsoLineSide side) const = 0;
  virtual void draw() const = 0;
};

//-----------------------------------------------------------------------------
// IsoLinePair declaration

class IsoLinePair : public IsoLineElement {
  const IsoLineElement* _children[2];
public:
  IsoLinePair(IsoLineElement* childLEFT_SIDE, IsoLineElement* childRIGHT_SIDE);
  ~IsoLinePair();

  float height(IsoLineSide side) const;
  void draw() const;
};

//-----------------------------------------------------------------------------
// IsoLineLeaf declaration

class IsoLineLeaf : public IsoLineElement {
  const MapUnit* _mapUnit;
public:
  IsoLineLeaf(const MapUnit* mapUnit);
  ~IsoLineLeaf();

  float height(IsoLineSide side) const;
  void draw() const;
};


//-----------------------------------------------------------------------------
// IsoLine functions

IsoLineElement* makeIsoLineTree(const IsoLine* isoLine, uint8_t indexLo, uint8_t indexHi) {
  if (indexLo == indexHi) {
    return new IsoLineLeaf(isoLine->unitAt(indexLo));
  }
  else {
    uint8_t indexMid = (indexLo + indexHi) / 2;
    return new IsoLinePair(
      makeIsoLineTree(isoLine, indexLo, indexMid),
      makeIsoLineTree(isoLine, indexMid+1, indexHi)
    );
  }
}

/*
//-----------------------------------------------------------------------------
// IsoLine implementation

IsoLine::IsoLine(Map* map, MapPos startPos) :
  _map(map),
  _startPos(startPos),
  _length(min(
    startPos.row + 1,
    map->numCols() - startPos.col
  )) {}

MapUnit* IsoLine::unitAt(uint8_t index) const {
  MapPos pos = _startPos;
  pos.col += index;
  pos.row -= index;
  return _map->unitAt(pos);
}

//-----------------------------------------------------------------------------
// IsoLinePair implementation

IsoLinePair::IsoLinePair(IsoLineElement* left, IsoLineElement* right) {
  _children[(int)LEFT_SIDE] = left;
  _children[(int)RIGHT_SIDE] = right;
}

IsoLinePair::~IsoLinePair() {
  delete _children[(int)LEFT_SIDE];
  delete _children[(int)RIGHT_SIDE];
}

float IsoLinePair::height(IsoLineSide side) const {
  return _children[(int)side]->height(side);
}

void IsoLinePair::draw() const {
  IsoLineSide lowerSide = (
    _children[(int)LEFT_SIDE]->height(RIGHT_SIDE) <
    _children[(int)RIGHT_SIDE]->height(LEFT_SIDE)
  ) ? LEFT_SIDE : RIGHT_SIDE;

  _children[(int)lowerSide]->draw();
  _children[1 - (int)lowerSide]->draw();
}


//-----------------------------------------------------------------------------
// IsoLineLeaf implementation

IsoLineLeaf::IsoLineLeaf(const MapUnit* mapUnit) :
  _mapUnit(mapUnit) {}

IsoLineLeaf::~IsoLineLeaf() {
  delete _mapUnit;
}

float IsoLineLeaf::height(IsoLineSide side) const {
  return _mapUnit->height();
}

void IsoLineLeaf::draw() const {
  _mapUnit->draw();
}

//-----------------------------------------------------------------------------
// MapUnit implementation

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
*/

//-----------------------------------------------------------------------------
// Map implementation

void Map::init(const LevelDef* levelDef) {
  _levelDef = levelDef;
}

/*
Map::Map(uint8_t numCols, uint8_t numRows) :
  _numCols(numCols + 2),
  _numRows(numRows + 2),
  _numIsoLines(numCols + numRows + 3) {

  // Create map units
  MapPos pos;

  _units = (MapUnit*) malloc(_numCols * _numRows * sizeof(MapUnit));
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

  // Create iso-lines needed to correctly draw map
  pos = (MapPos){ .col = 0, .row = 0};
  _isoLines = (IsoLineElement**) malloc(_numIsoLines * sizeof(IsoLineElement*));
  for (uint8_t i = 0; i < _numIsoLines; i++) {
    IsoLine isoLine = IsoLine(this, pos);
    if (pos.row < _numRows - 1) {
      pos.row++;
    } else {
      pos.col++;
    }
    _isoLines[i] = makeIsoLineTree(&isoLine, 0, isoLine.length() - 1);
  }

  _wave = new DirectionalWave(0.10);
  _wave->setAmplitude(1);
  _waveStrength = 0;
  _waveStrengthDelta = 0.5;
}
*/

/*
void Map::update() {
  _waveStrength = max(0.5, min(1, _waveStrength + _waveStrengthDelta));

  MapPos pos;
  for (pos.col = 0; pos.col < _numCols; pos.col++) {
    for (pos.row = 0; pos.row < _numRows; pos.row++) {
      float waveHeight = smoothClamp( _wave->eval(pos) );

      unitAt(pos)->setWave(waveHeight);
    }
  }
}
*/

void Map::draw() {
  MapPos pos;
  for (pos.col = 0; pos.col < numCols(); pos.col++) {
    for (pos.row = 0; pos.row < numRows(); pos.row++) {
      uint8_t tile = _levelDef->mapDef.tiles[pos.col + pos.row * maxCols];
      TileType tileType = tileTypes[tile & 0x1f];
      uint8_t height0 = 2 * (tile & 0xe0) >> 5 + tileType.height0;
      int8_t x = (pos.col - pos.row) * 8 + 32;
      int8_t y = (pos.col + pos.row) * 4 - height0;

      uint8_t frame = tileType.spriteIndex;
      for (uint8_t i = 0; i < tileType.spriteHeight; i++) {
        mapTilesImage.setFrame(frame++);
        gb.display.drawImage(x, y, mapTilesImage);
        y += 8;
      }
    }
  }
}

