#include "Levels.h"

#include "Globals.h"

const uint8_t H0 = 0x00;
const uint8_t H1 = 0x20;
const uint8_t H2 = 0x40;
const uint8_t H3 = 0x60;
const uint8_t H4 = 0x80;
const uint8_t H5 = 0xa0;
const uint8_t H6 = 0xc0;
const uint8_t H7 = 0xe0;

const TilePos enemyStartPosLevel1[1] = { makeTilePos(6, 1) };
const TilePos enemyStartPosLevel2[2] = { makeTilePos(4, 0), makeTilePos(4, 1) };
const TilePos enemyStartPosLevel3[3] = { makeTilePos(7, 0), makeTilePos(0, 7) };

const TilePos pickupStartPosLevel0[13] = {
  makeTilePos(0, 0), makeTilePos(0, 2), makeTilePos(0, 3), makeTilePos(0, 5), makeTilePos(0, 7),
  makeTilePos(2, 1), makeTilePos(2, 3), makeTilePos(2, 5), makeTilePos(2, 7),
  makeTilePos(7, 0), makeTilePos(7, 2), makeTilePos(7, 4), makeTilePos(7, 6),
};
const TilePos pickupStartPosLevel1[4] = {
  makeTilePos(0, 0), makeTilePos(0, 7), makeTilePos(7, 0), makeTilePos(7, 7)
};
const TilePos pickupStartPosLevel2[6] = {
  makeTilePos(0, 0), makeTilePos(7, 0),
  makeTilePos(2, 2), makeTilePos(6, 2), makeTilePos(2, 6), makeTilePos(6, 6),
};
const TilePos pickupStartPosLevel3[3] = {
  makeTilePos(0, 0), makeTilePos(4, 0), makeTilePos(0, 4)
};

const LevelSpec levelSpecs[numLevels] = {
  // 0: Going Down
  LevelSpec {
    .playerStartPos = makeTilePos(1, 1),
    .numEnemies = 0,
    .enemyStartPos = (const TilePos*)0,
    .numPickups = 13,
    .pickupStartPos = pickupStartPosLevel0,
    .timeLimitInCycles = 1500,
    .tilesSpec = TilesSpec {
      .tiles = {
        0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7,
        0x00|H7, 0x00|H7, 0x00|H6, 0x00|H6, 0x00|H6, 0x00|H6, 0x00|H6, 0x00|H6,
        0x00|H7, 0x00|H7, 0x00|H5, 0x00|H5, 0x00|H5, 0x00|H5, 0x00|H5, 0x00|H5,
        0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4,
        0x00|H4, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3,
        0x00|H4, 0x00|H3, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2,
        0x00|H4, 0x00|H3, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1,
        0x00|H4, 0x00|H3, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0
      }
    }
  },

  // Ride the Waves
  LevelSpec {
    .playerStartPos = makeTilePos(2, 5),
    .numEnemies = 1,
    .enemyStartPos = enemyStartPosLevel1,
    .numPickups = 4,
    .pickupStartPos = pickupStartPosLevel1,
    .timeLimitInCycles = 3000,
    .tilesSpec = TilesSpec {
      .tiles = {
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
        0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0
      }
    }
  },

  // Gutter and Stage
  LevelSpec {
    .playerStartPos = makeTilePos(3, 7),
    .numEnemies = 2,
    .enemyStartPos = enemyStartPosLevel2,
    .numPickups = 6,
    .pickupStartPos = pickupStartPosLevel2,
    .timeLimitInCycles = 4500,
    .tilesSpec = TilesSpec {
      .tiles = {
        0x07|H0, 0x04|H4, 0x05|H4, 0x06|H4, 0x04|H4, 0x05|H4, 0x06|H4, 0x07|H1,
        0x02|H0, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1,
        0x02|H0, 0x02|H1, 0x02|H2, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H2, 0x02|H1,
        0x02|H0, 0x02|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H1,
        0x02|H0, 0x02|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H1,
        0x02|H0, 0x02|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H1,
        0x02|H0, 0x02|H1, 0x02|H2, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H2, 0x02|H1,
        0x03|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1
      }
    }
  },

  // Barsaman
  LevelSpec {
    .playerStartPos = makeTilePos(7, 7),
    .numEnemies = 2,
    .enemyStartPos = enemyStartPosLevel3,
    .numPickups = 3,
    .pickupStartPos = pickupStartPosLevel3,
    .timeLimitInCycles = 3000,
    .tilesSpec = TilesSpec {
      .tiles = {
        0x09|H7, 0x08|H6, 0x08|H5, 0x08|H3, 0x09|H6, 0x08|H4, 0x08|H3, 0x08|H2,
        0x08|H2, 0x08|H3, 0x08|H4, 0x08|H2, 0x08|H5, 0x08|H3, 0x08|H3, 0x08|H2,
        0x08|H4, 0x08|H5, 0x08|H5, 0x08|H3, 0x08|H5, 0x08|H2, 0x08|H3, 0x08|H1,
        0x08|H5, 0x08|H2, 0x08|H4, 0x08|H2, 0x08|H4, 0x08|H3, 0x08|H2, 0x08|H1,
        0x09|H6, 0x08|H2, 0x08|H4, 0x08|H2, 0x08|H1, 0x08|H1, 0x08|H1, 0x08|H1,
        0x08|H3, 0x08|H2, 0x08|H4, 0x08|H3, 0x08|H1, 0x08|H0, 0x08|H0, 0x08|H0,
        0x08|H2, 0x08|H2, 0x08|H2, 0x08|H2, 0x08|H1, 0x08|H0, 0x08|H0, 0x08|H0,
        0x08|H1, 0x08|H3, 0x08|H2, 0x08|H1, 0x08|H1, 0x08|H0, 0x08|H0, 0x08|H0
      }
    }
  },

#ifdef TEST_LEVELS
  // Testing level: falling
  LevelSpec {
    .playerStartPos = makeTilePos(2, 5),
    .numEnemies = 1,
    .enemyStartPos = enemyStartPosLevel1,
    .tilesSpec = TilesSpec {
      .tiles = {
        0x00|H7, 0x00|H7, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4,
        0x00|H7, 0x00|H7, 0x00|H3, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H7, 0x00|H7, 0x00|H2, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H7, 0x00|H7, 0x00|H1, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H7, 0x00|H7, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H7, 0x00|H7, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H7, 0x00|H7, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x02|H3
      }
    }
  },

  // Testing level: drawing
  LevelSpec {
    .playerStartPos = makeTilePos(2, 5),
    .numEnemies = 1,
    .enemyStartPos = enemyStartPosLevel1,
    .tilesSpec = TilesSpec {
      .tiles = {
        0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H0, 0x00|H4, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H4, 0x00|H0,
        0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H0, 0x00|H0, 0x00|H0, 0x00|H2, 0x00|H2, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H0, 0x00|H0, 0x00|H0, 0x00|H2, 0x00|H2, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
        0x00|H0, 0x00|H4, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H4, 0x00|H0,
        0x00|H0, 0x00|H4, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x02|H0
      }
    }
  }
#endif
};

struct TimebarSpec {
  uint8_t len;
  uint8_t unit;
  ColorIndex colorMain;
  ColorIndex colorDark;
};

const TimebarSpec timebarSpecs[6] = {
  {.len = 4, .unit =  1, .colorMain = INDEX_RED, .colorDark = INDEX_PURPLE},
  {.len = 4, .unit =  2, .colorMain = INDEX_ORANGE, .colorDark = INDEX_BROWN},
  {.len = 8, .unit =  4, .colorMain = INDEX_YELLOW, .colorDark = INDEX_ORANGE},
  {.len = 8, .unit =  8, .colorMain = INDEX_LIGHTGREEN, .colorDark = INDEX_GREEN},
  {.len = 8, .unit = 16, .colorMain = INDEX_LIGHTGREEN, .colorDark = INDEX_GREEN},
  {.len = 8, .unit = 32, .colorMain = INDEX_LIGHTGREEN, .colorDark = INDEX_GREEN}
};

void Level::drawTimeBar() {
  int8_t x = 78;
  int16_t t = _cyclesRemaining;
  const TimebarSpec *spec = timebarSpecs;
  while (t > 0) {
    uint8_t len = min(spec->len, 1 + t / (spec->unit * 25));

    if (len > 0) {
      gb.display.setColor(spec->colorMain);
      gb.display.fillRect(x - len + 1, 1, len, 2);

      gb.display.setColor(spec->colorDark);
      gb.display.drawFastHLine(x - len + 1, 3, len);
    }

    t -= spec->len * spec->unit * 25;
    if (t <= 0) {
      break;
    }
    x -= spec->len;
    spec++;
  }

  // Flash lights when time is running out
  if (spec->colorDark != INDEX_GREEN && !_frozen) {
    uint8_t i = gb.frameCount % (spec->unit * 25);
    if (i < 12) {
      gb.lights.drawPixel(0, 3 - i / 3, spec->colorMain);
      gb.lights.drawPixel(1, i / 3, spec->colorMain);
    }
  }
}

void Level::init(const LevelSpec *levelSpec) {
  _levelSpec = levelSpec;

  tiles->init(&_levelSpec->tilesSpec);

  numMovers = 0;

  // Create player
  _player.init(numMovers++);
  movers[_player.index()] = &_player;

  // Create enemies
  for (uint8_t i = 0; i < _levelSpec->numEnemies; i++) {
    assertTrue(numMovers < maxNumMovers);

    _enemies[i].init(numMovers++, _player.index());
    movers[_enemies[i].index()] = &_enemies[i];
  }

  numObjects = 0;

  // Create and place pick-ups
  for (uint8_t i = 0; i < _levelSpec->numPickups; i++) {
    assertTrue(numObjects < maxNumObjects);

    _pickups[i].init(numObjects++);
    objects[_pickups[i].index()] = &_pickups[i];

    tiles->putObjectOnTile(_pickups[i].index(), _levelSpec->pickupStartPos[i]);
  }
  _numPickupsCollected = 0;
}

void Level::reset() {
  tiles->reset(&_levelSpec->tilesSpec);

  // Reset all objects
  for (int8_t i = numObjects; --i >= 0; ) {
    objects[i]->reset();
  }

  _started = false;
  _frozen = false;

  _cyclesRemaining = _levelSpec->timeLimitInCycles;
}

void Level::start() {
  _player.reset();
  tiles->putMoverOnTile(_player.index(), _levelSpec->playerStartPos);

  for (int8_t i = _levelSpec->numEnemies; --i >= 0; ) {
    _enemies[i].reset();
    tiles->putMoverOnTile(_enemies[i].index(), _levelSpec->enemyStartPos[i]);
  }

  _started = true;
}

void Level::freeze() {
  tiles->attenuateWaves();

  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->freeze();
  }

  _frozen = true;
}

bool Level::isCompleted() {
  return _numPickupsCollected == _levelSpec->numPickups;
}

void Level::update() {
  tiles->update();

  if (_started) {
    for (int8_t i = numMovers; --i >= 0; ) {
      movers[i]->update();
    }
  }

  if (--_cyclesRemaining == 0) {
    signalDeath("Timed out");
  }
}

void Level::draw() {
  tiles->draw(_started ? &_player : 0);

  drawTimeBar();
}
