#include "Tiles.h"

#include "Globals.h"
#include "ImageData.h"
#include "Movers.h"
#include "TileTypes.h"
#include "Waves.h"
#include "Palettes.h"

#include <assert.h>

Tiles _tiles = Tiles();

// Exposed in Globals.h
Tiles* tiles = &_tiles;

enum IsoLineSide {
  LEFT_SIDE = 0,
  RIGHT_SIDE = 1
};

//-----------------------------------------------------------------------------
// IsoLine declaration

class IsoLine {
  const Tiles* _map;
  const TilePos _startPos;
  const uint8_t _length;

public:
  IsoLine(Tiles* map, TilePos start);

  uint8_t length() { return _length; }
  Tile* unitAt(uint8_t index) const;
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
  const Tile* _mapUnit;
public:
  IsoLineLeaf(const Tile* mapUnit);
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

IsoLine::IsoLine(Tiles* map, TilePos startPos) :
  _map(map),
  _startPos(startPos),
  _length(min(
    startPos.row + 1,
    map->numCols() - startPos.col
  )) {}

Tile* IsoLine::unitAt(uint8_t index) const {
  TilePos pos = _startPos;
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

IsoLineLeaf::IsoLineLeaf(const Tile* mapUnit) :
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
*/

//-----------------------------------------------------------------------------
// Tile implementation

// Empty constructor to enable usage in array.
// Entries should be initialized using init() method before usage.
Tile::Tile() {}

void Tile::init(int8_t height0) {
  _height0 = height0;
  _height = height0;

  _moverIndex = -1;
}

void Tile::setWave(int8_t waveHeight) {
  _height = _height0 + waveHeight;
}

void Tile::draw(TilePos pos, TileType* tileType) const {
  int8_t col = colOfPos(pos);
  int8_t row = rowOfPos(pos);
  int8_t x = (col - row) * 8 + 32;
  int8_t y = (col + row) * 4 - _height;

  if (x <= -16 || x >= 80) {
    return;
  }

  if (!(tileType->flags & TILEFLAG_CHECKERED) || (col + row) % 2) {
    gb.display.colorIndex = (Color *)palettes[tileType->paletteIndex];
  }

  // Draw top image (which has transparency)
  uint8_t imageIndex = tileType->topImageIndex;
  int8_t dy = tileImageInfo[imageIndex].dy;
  tileImages[imageIndex].setFrame(tileType->topFrameIndex);
  gb.display.drawImage(x + tileImageInfo[imageIndex].dx, y + dy, tileImages[imageIndex]);
  dy += tileImages[imageIndex].height();

  // Draw bottom image (without transparency)
  imageIndex = tileType->bottomImageIndex;
  dy += tileImageInfo[imageIndex].dy;
  tileImages[imageIndex].setFrame(tileType->bottomFrameIndex);
  gb.display.drawImage(x + tileImageInfo[imageIndex].dx, y + dy, tileImages[imageIndex]);

  gb.display.colorIndex = (Color *)palettes[PALETTE_DEFAULT];

  if (_moverIndex >= 0) {
    movers[_moverIndex]->draw(x + 4, y - 2);
  }
}

//-----------------------------------------------------------------------------
// Tiles implementation

Tiles::Tiles() :
  _wave(-0.1 * 2 * PI) {

  _wave.setAmplitude(1);
}

void Tiles::init(const LevelSpec* levelSpec) {
  _levelSpec = levelSpec;

  for (TilePos pos = maxTilePos; --pos >= 0; ) {
    uint8_t tile = _levelSpec->tilesSpec.tiles[pos];
    TileType tileType = tileTypes[tile & 0x1f];

    int8_t height0 = tileType.height0 + 2 * (tile & 0xe0) >> 5;
    _units[pos].init(height0);
  }

  _waveStrength = 0;
  _waveStrengthDelta = 0.5;
}

/*
Tiles::Tiles(uint8_t numCols, uint8_t numRows) :
  _numCols(numCols + 2),
  _numRows(numRows + 2),
  _numIsoLines(numCols + numRows + 3) {

  // Create map units
  TilePos pos;

  _units = (Tile*) malloc(_numCols * _numRows * sizeof(Tile));
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
  pos = (TilePos){ .col = 0, .row = 0};
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
}
*/

int8_t Tiles::neighbour(int8_t tileIndex, Heading heading) {
  TilePos tilePos = (TilePos)tileIndex;
  int8_t col = colOfPos(tilePos) + colDelta[heading];
  int8_t row = rowOfPos(tilePos) + rowDelta[heading];
  if (col < 0 || col >= numCols() || row < 0 || row >= numRows()) {
    return -1;
  }
  return makeTilePos(col, row);
}

void Tiles::addMover(int8_t tileIndex, int8_t moverIndex) {
  Mover* mover = movers[moverIndex];

  if (mover->_drawTileIndex >= 0) {
    // Remove from current tile
    assert(_units[mover->_drawTileIndex]._moverIndex == moverIndex);

    // TODO: Update when supporting multiple movers on one tile
    _units[mover->_drawTileIndex]._moverIndex = -1;
  } else {
    mover->_tileIndex = tileIndex;
  }

  mover->_drawTileIndex = tileIndex;
  // TODO: Update when supporting multiple movers on one tile
  _units[mover->_drawTileIndex]._moverIndex = moverIndex;
}

void Tiles::update() {
  _waveStrength = max(0.5, min(1, _waveStrength + _waveStrengthDelta));

  for (TilePos pos = maxTilePos; --pos >= 0; ) {
    uint8_t tile = _levelSpec->tilesSpec.tiles[pos];
    TileType tileType = tileTypes[tile & 0x1f];

    if (tileType.flexibility) {
      //float waveHeight = smoothStep( _wave.eval(pos) );
      float waveHeight = _wave.eval(pos);
      int8_t actualHeight = round(waveHeight * tileType.flexibility);

      _units[pos].setWave(actualHeight);
    }
  }
}

void Tiles::draw() {
  for (TilePos pos = 0; pos < maxTilePos; pos++) {
    uint8_t tile = _levelSpec->tilesSpec.tiles[pos];
    TileType tileType = tileTypes[tile & 0x1f];
    _units[pos].draw(pos, &tileType);
  }
}

