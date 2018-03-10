#include "Utils.h"

#include "Levels.h"

class Map;
class Wave;
class Mover;
class IsoLineElement;

/*
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
    float height() const {
      return _height;
    }

    void addMover(Mover* mover);
    void removeMover(Mover* mover);

    MapUnit* const neighbour(Heading heading);

    void draw() const;
};
*/

class Map {
    const LevelDef* _levelDef;

    // 1D-array of MapUnits, representing a 2D map
    //MapUnit _units[maxCols * maxRows];

    // 1D-array of IsoLineElement pointers
    //const uint8_t _numIsoLines;
    //IsoLineElement** _isoLines;

    //Wave* _wave;
    //float _waveStrength;
    //float _waveStrengthDelta;

public:
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

