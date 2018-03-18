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

const TilePos pickupStartPosLevel0[13] = {
  makeTilePos(0, 0), makeTilePos(0, 2), makeTilePos(0, 3), makeTilePos(0, 5), makeTilePos(0, 7),
  makeTilePos(2, 1), makeTilePos(2, 3), makeTilePos(2, 5), makeTilePos(2, 7),
  makeTilePos(7, 0), makeTilePos(7, 2), makeTilePos(7, 4), makeTilePos(7, 6),
};
const TilePos pickupStartPosLevel1[4] = {
  makeTilePos(0, 0), makeTilePos(0, 7), makeTilePos(7, 0), makeTilePos(7, 7)
};

const LevelSpec levelSpecs[numLevels] = {
  // 0: Going Down
  LevelSpec {
    .playerStartPos = makeTilePos(1, 1),
    .numEnemies = 0,
    .enemyStartPos = (const TilePos*)0,
    .numPickups = 13,
    .pickupStartPos = pickupStartPosLevel0,
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

void Level::init(const LevelSpec *levelSpec) {
  _levelSpec = levelSpec;

  tiles->init(&_levelSpec->tilesSpec);

  numMovers = 0;

  // Create player
  _player.init(numMovers++);
  movers[_player.index()] = &_player;

  // Create enemies
  for (uint8_t i = 0; i < _levelSpec->numEnemies; i++) {
    assert(numMovers < maxNumMovers);

    _enemies[i].init(numMovers++, _player.index());
    movers[_enemies[i].index()] = &_enemies[i];
  }

  numObjects = 0;

  // Create and place pick-ups
  for (uint8_t i = 0; i < _levelSpec->numPickups; i++) {
    assert(numObjects < maxNumObjects);

    _pickups[i].init(numObjects++);
    objects[_pickups[i].index()] = &_pickups[i];

    tiles->putObjectOnTile(_pickups[i].index(), _levelSpec->pickupStartPos[i]);
  }
  _numPickupsCollected = 0;

  Level::reset();
}

void Level::reset() {
  tiles->reset(&_levelSpec->tilesSpec);

  _player.reset();
  tiles->putMoverOnTile(_player.index(), _levelSpec->playerStartPos);

  for (int8_t i = _levelSpec->numEnemies; --i >= 0; ) {
    _enemies[i].reset();
    tiles->putMoverOnTile(_enemies[i].index(), _levelSpec->enemyStartPos[i]);
  }

  // Reset all objects
  for (int8_t i = numObjects; --i >= 0; ) {
    objects[i]->reset();
  }
}

bool Level::isCompleted() {
  return _numPickupsCollected == _levelSpec->numPickups;
}

void Level::update() {
  tiles->update();
  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->update();
  }
}

void Level::draw() {
  tiles->draw(&_player);
}

