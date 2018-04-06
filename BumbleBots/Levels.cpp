/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Levels.h"

#include "Globals.h"
#include "Palettes.h"
#include "TileTypes.h"

//-----------------------------------------------------------------------------
// Level definitions

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
const TilePos enemyStartPosLevel4[1] = { makeTilePos(1, 1) };
const TilePos enemyStartPosLevel6[1] = { makeTilePos(0, 0) };
const TilePos enemyStartPosTestLevel0[1] = { makeTilePos(7, 1) };

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
const TilePos pickupStartPosLevel4[6] = {
  makeTilePos(3, 0), makeTilePos(0, 3),
  makeTilePos(3, 5), makeTilePos(5, 3),
  makeTilePos(3, 7), makeTilePos(7, 3)
};
const TilePos pickupStartPosLevel5[8] = {
  makeTilePos(0, 0), makeTilePos(0, 7), makeTilePos(7, 0), makeTilePos(7, 7),
  makeTilePos(1, 4), makeTilePos(4, 1), makeTilePos(5, 6), makeTilePos(6, 3)
};
const TilePos pickupStartPosLevel6[4] = {
  makeTilePos(1, 1), makeTilePos(6, 1),
  makeTilePos(1, 6), makeTilePos(6, 6)
};
const TilePos pickupStartPosLevel7[1] = {
  makeTilePos(0, 2)
};

const TeleportPairSpec teleportSpecsLevel4[4] = {
  TeleportPairSpec {
    .tile1 = makeTilePos(3, 3),
    .tile2 = makeTilePos(0, 7),
    .paletteIndex = PALETTE_TELEPORT1
  },
  TeleportPairSpec {
    .tile1 = makeTilePos(3, 4),
    .tile2 = makeTilePos(7, 7),
    .paletteIndex = PALETTE_TELEPORT2
  },
  TeleportPairSpec {
    .tile1 = makeTilePos(4, 3),
    .tile2 = makeTilePos(0, 0),
    .paletteIndex = PALETTE_TELEPORT3
  },
  TeleportPairSpec {
    .tile1 = makeTilePos(4, 4),
    .tile2 = makeTilePos(7, 0),
    .paletteIndex = PALETTE_TELEPORT4
  }
};
const TeleportPairSpec teleportSpecsLevel7[4] = {
  TeleportPairSpec {
    .tile1 = makeTilePos(4, 2),
    .tile2 = makeTilePos(6, 3),
    .paletteIndex = PALETTE_TELEPORT1
  },
  TeleportPairSpec {
    .tile1 = makeTilePos(6, 2),
    .tile2 = makeTilePos(0, 3),
    .paletteIndex = PALETTE_TELEPORT2
  },
  TeleportPairSpec {
    .tile1 = makeTilePos(2, 3),
    .tile2 = makeTilePos(4, 4),
    .paletteIndex = PALETTE_TELEPORT3
  },
  TeleportPairSpec {
    .tile1 = makeTilePos(4, 3),
    .tile2 = makeTilePos(2, 4),
    .paletteIndex = PALETTE_TELEPORT4
  }
};

const GapSpec gapSpecsLevel6[4] = {
  GapSpec {
    .pos = makeTilePos(2, 1),
    .paletteIndex = PALETTE_GAP_DEFAULT
  },
  GapSpec {
    .pos = makeTilePos(3, 1),
    .paletteIndex = PALETTE_GAP_DEFAULT
  },
  GapSpec {
    .pos = makeTilePos(1, 2),
    .paletteIndex = PALETTE_GAP_DEFAULT
  },
  GapSpec {
    .pos = makeTilePos(2, 2),
    .paletteIndex = PALETTE_GAP_DEFAULT
  }
};
const GapSpec gapSpecsLevel7[1] = {
  GapSpec {
    .pos = makeTilePos(2, 2),
    .paletteIndex = PALETTE_GAP_DEFAULT
  }
};

const TilePos boxStartPosLevel6[4] = {
  makeTilePos(2, 4), makeTilePos(2, 5), makeTilePos(4, 3), makeTilePos(6, 3)
};
const TilePos boxStartPosLevel7[1] = {
  makeTilePos(3, 5)
};
const TilePos boxStartPosTestLevel0[17] = {
  makeTilePos(1, 0), makeTilePos(1, 1), makeTilePos(1, 2), makeTilePos(1, 3), makeTilePos(1, 4), makeTilePos(1, 5), makeTilePos(1, 6),
  makeTilePos(2, 0), makeTilePos(2, 1), makeTilePos(2, 2), makeTilePos(2, 3), makeTilePos(2, 4),
  makeTilePos(6, 0), makeTilePos(6, 1), makeTilePos(6, 2),
  makeTilePos(6, 5), makeTilePos(7, 5)
};

const uint8_t tilesLevel0[maxTiles] = {
  0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7,
  0x00|H7, 0x00|H7, 0x00|H6, 0x00|H6, 0x00|H6, 0x00|H6, 0x00|H6, 0x00|H6,
  0x00|H7, 0x00|H7, 0x00|H5, 0x00|H5, 0x00|H5, 0x00|H5, 0x00|H5, 0x00|H5,
  0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4,
  0x00|H4, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3, 0x00|H3,
  0x00|H4, 0x00|H3, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2,
  0x00|H4, 0x00|H3, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1,
  0x00|H4, 0x00|H3, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0
};
const uint8_t tilesLevel1[maxTiles] = {
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0,
  0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0, 0x01|H0
};
const uint8_t tilesLevel2[maxTiles] = {
  0x07|H0, 0x04|H4, 0x05|H4, 0x06|H4, 0x04|H4, 0x05|H4, 0x06|H4, 0x07|H1,
  0x02|H0, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1,
  0x02|H0, 0x02|H1, 0x02|H2, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H2, 0x02|H1,
  0x02|H0, 0x02|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H1,
  0x02|H0, 0x02|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H1,
  0x02|H0, 0x02|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H1,
  0x02|H0, 0x02|H1, 0x02|H2, 0x03|H1, 0x03|H1, 0x03|H1, 0x02|H2, 0x02|H1,
  0x03|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1, 0x02|H1
};
const uint8_t tilesLevel3[maxTiles] = {
  0x09|H7, 0x08|H6, 0x08|H5, 0x08|H3, 0x09|H6, 0x08|H4, 0x08|H3, 0x08|H2,
  0x08|H2, 0x08|H3, 0x08|H4, 0x08|H2, 0x08|H5, 0x08|H3, 0x08|H3, 0x08|H2,
  0x08|H4, 0x08|H5, 0x08|H5, 0x08|H3, 0x08|H5, 0x08|H2, 0x08|H3, 0x08|H1,
  0x08|H5, 0x08|H2, 0x08|H4, 0x08|H2, 0x08|H4, 0x08|H3, 0x08|H2, 0x08|H1,
  0x09|H6, 0x08|H2, 0x08|H4, 0x08|H2, 0x08|H1, 0x08|H1, 0x08|H1, 0x08|H1,
  0x08|H3, 0x08|H2, 0x08|H4, 0x08|H3, 0x08|H1, 0x08|H0, 0x08|H0, 0x08|H0,
  0x08|H2, 0x08|H2, 0x08|H2, 0x08|H2, 0x08|H1, 0x08|H0, 0x08|H0, 0x08|H0,
  0x08|H1, 0x08|H3, 0x08|H2, 0x08|H1, 0x08|H1, 0x08|H0, 0x08|H0, 0x08|H0
};
const uint8_t tilesLevel4[maxTiles] = {
  0x00|H4, 0x00|H4, 0x00|H4, 0x00|H3, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2,
  0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2,
  0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2,
  0x00|H3, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H2, 0x00|H1, 0x00|H2, 0x00|H1,
  0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H2, 0x00|H2, 0x00|H2, 0x00|H1, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H2, 0x00|H2, 0x00|H2, 0x00|H2, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H2, 0x00|H2, 0x00|H2, 0x00|H1, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0
};
const uint8_t* tilesLevel5 = tilesLevel1;
const uint8_t tilesLevel6[maxTiles] = {
  0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0,
  0x0b|H0, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x0a|H2, 0x00|H1, 0x0b|H0,
  0x0b|H0, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x0a|H2, 0x00|H1, 0x0b|H0,
  0x0b|H0, 0x0a|H2, 0x0a|H2, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x0b|H0,
  0x0b|H0, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x0a|H2, 0x00|H1, 0x0b|H0,
  0x0b|H0, 0x00|H1, 0x00|H1, 0x00|H1, 0x00|H1, 0x0a|H2, 0x00|H1, 0x0b|H0,
  0x0b|H0, 0x00|H1, 0x0a|H2, 0x0a|H2, 0x00|H1, 0x00|H1, 0x00|H1, 0x0b|H0,
  0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0, 0x0b|H0,
};
const uint8_t tilesLevel7[maxTiles] = {
  0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0,
  0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0,
  0x02|H7, 0x02|H7, 0x02|H7, 0x02|H7, 0x02|H7, 0x02|H7, 0x02|H7, 0x0c|H0,
  0x02|H5, 0x02|H5, 0x02|H5, 0x02|H5, 0x02|H5, 0x02|H5, 0x02|H5, 0x0c|H0,
  0x02|H3, 0x03|H1, 0x02|H2, 0x02|H2, 0x02|H2, 0x03|H1, 0x02|H3, 0x0c|H0,
  0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x0c|H0,
  0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x02|H0, 0x0c|H0,
  0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0, 0x0c|H0,
};
const uint8_t tilesTestLevel0[maxTiles] = {
  0x00|H7, 0x00|H7, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4, 0x00|H4,
  0x00|H7, 0x00|H7, 0x00|H3, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H7, 0x00|H7, 0x00|H2, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H7, 0x00|H7, 0x00|H1, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H7, 0x00|H7, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H7, 0x00|H7, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H7, 0x00|H7, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0, 0x00|H0,
  0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x00|H7, 0x07|H0
};

const LevelSpec levelSpecs[numLevels] = {
  LevelSpec {
    .title = "Going Down",
    .playerStartPos = makeTilePos(1, 1),
    .numEnemies = 0,
    .enemyStartPos = nullptr,
    .numPickups = 13,
    .pickupStartPos = pickupStartPosLevel0,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 0,
    .boxStartPos = nullptr,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = 2000,
    .tilesSpec = LevelTilesSpec(tilesLevel0)
  },

  LevelSpec {
    .title = "Ride the Waves",
    .playerStartPos = makeTilePos(2, 5),
    .numEnemies = 1,
    .enemyStartPos = enemyStartPosLevel1,
    .numPickups = 4,
    .pickupStartPos = pickupStartPosLevel1,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 0,
    .boxStartPos = nullptr,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = 3000,
    .tilesSpec = LevelTilesSpec(tilesLevel1)
  },

  LevelSpec {
    .title = "Gutter and Stage",
    .playerStartPos = makeTilePos(3, 7),
    .numEnemies = 2,
    .enemyStartPos = enemyStartPosLevel2,
    .numPickups = 6,
    .pickupStartPos = pickupStartPosLevel2,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 0,
    .boxStartPos = nullptr,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = 4500,
    .tilesSpec = LevelTilesSpec(tilesLevel2)
  },

  LevelSpec {
    .title = "Barsaman",
    .playerStartPos = makeTilePos(7, 7),
    .numEnemies = 2,
    .enemyStartPos = enemyStartPosLevel3,
    .numPickups = 3,
    .pickupStartPos = pickupStartPosLevel3,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 0,
    .boxStartPos = nullptr,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = 3000,
    .tilesSpec = LevelTilesSpec(tilesLevel3)
  },

  LevelSpec {
    .title = "Telerium",
    .playerStartPos = makeTilePos(5, 5),
    .numEnemies = 1,
    .enemyStartPos = enemyStartPosLevel4,
    .numPickups = 6,
    .pickupStartPos = pickupStartPosLevel4,
    .numTeleportPairs = 4,
    .teleportSpecs = teleportSpecsLevel4,
    .numBoxes = 0,
    .boxStartPos = nullptr,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = 3000,
    .tilesSpec = LevelTilesSpec(tilesLevel4)
  },

  LevelSpec {
    .title = "Aquatic Race",
    .playerStartPos = makeTilePos(3, 3),
    .numEnemies = 0,
    .enemyStartPos = nullptr,
    .numPickups = 8,
    .pickupStartPos = pickupStartPosLevel5,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 0,
    .boxStartPos = nullptr,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = -1000,
    .tilesSpec = LevelTilesSpec(tilesLevel5)
  },

  LevelSpec {
    .title = "Mind the Gap",
    .playerStartPos = makeTilePos(4, 4),
    .numEnemies = 1,
    .enemyStartPos = enemyStartPosLevel6,
    .numPickups = 4,
    .pickupStartPos = pickupStartPosLevel6,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 4,
    .boxStartPos = boxStartPosLevel6,
    .numGaps = 4,
    .gapSpecs = gapSpecsLevel6,
    .timeLimitInCycles = 3000,
    .tilesSpec = LevelTilesSpec(tilesLevel6)
  },

  LevelSpec {
    .title = "Going Up",
    .playerStartPos = makeTilePos(3, 6),
    .numEnemies = 0,
    .enemyStartPos = nullptr,
    .numPickups = 1,
    .pickupStartPos = pickupStartPosLevel7,
    .numTeleportPairs = 4,
    .teleportSpecs = teleportSpecsLevel7,
    .numBoxes = 1,
    .boxStartPos = boxStartPosLevel7,
    .numGaps = 1,
    .gapSpecs = gapSpecsLevel7,
    .timeLimitInCycles = 3000,
    .tilesSpec = LevelTilesSpec(tilesLevel7)
  },

#ifdef TEST_LEVELS
  // Testing level: falling & boxes
  LevelSpec {
    .title = "Test Boxes",
    .playerStartPos = makeTilePos(2, 5),
    .numEnemies = 0,
    .enemyStartPos = enemyStartPosTestLevel0,
    .numPickups = 4,
    .pickupStartPos = pickupStartPosLevel1,
    .numTeleportPairs = 0,
    .teleportSpecs = nullptr,
    .numBoxes = 17,
    .boxStartPos = boxStartPosTestLevel0,
    .numGaps = 0,
    .gapSpecs = nullptr,
    .timeLimitInCycles = 3000,
    .tilesSpec = LevelTilesSpec(tilesTestLevel0)
  }
#endif
};

//-----------------------------------------------------------------------------
// LevelTilesSpec implementation

LevelTilesSpec::LevelTilesSpec(const uint8_t* tiles) :
  _tiles(tiles) {}

int8_t LevelTilesSpec::baselineHeightAt(TilePos pos) const {
  uint8_t tile = _tiles[pos];

  return tileTypes[tile & 0x1f].height0 + 2 * ((tile & 0xe0) >> 5);
}

TileType* LevelTilesSpec::tileTypeAt(TilePos pos) const {
  return &tileTypes[_tiles[pos] & 0x1f];
}

//-----------------------------------------------------------------------------
// Level implementation

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

void Level::initPlayer() {
  // Create player
  _player.init(numMovers++);
  movers[_player.index()] = &_player;
}

void Level::initEnemies() {
  // Create enemies
  for (uint8_t i = 0; i < _levelSpec->numEnemies; i++) {
    assertTrue(numMovers < maxNumMovers);

    _enemies[i].init(numMovers++, _player.index());
    movers[_enemies[i].index()] = &_enemies[i];
  }
}

void Level::initBoxes() {
  // Create boxes
  for (uint8_t i = 0; i < _levelSpec->numBoxes; i++) {
    assertTrue(numMovers < maxNumMovers);

    _boxes[i].init(numMovers++);
    movers[_boxes[i].index()] = &_boxes[i];
  }
}

void Level::initMovers() {
  numMovers = 0;

  initPlayer();
  initEnemies();
  initBoxes();
}

void Level::initPickups() {
  for (uint8_t i = 0; i < _levelSpec->numPickups; i++) {
    assertTrue(numObjects < maxNumObjects);

    _pickups[i].init(numObjects++);
    objects[_pickups[i].index()] = &_pickups[i];

    tiles->putObjectOnTile(_pickups[i].index(), _levelSpec->pickupStartPos[i]);
  }
  _numPickupsCollected = 0;
}

void Level::initTeleports() {
  uint8_t j = 0;
  for (uint8_t i = 0; i < _levelSpec->numTeleportPairs; i++) {
    TeleportPairSpec spec = _levelSpec->teleportSpecs[i];

    assertTrue(numObjects < maxNumObjects);
    _teleports[j].init(numObjects++, spec.tile2, spec.paletteIndex);
    objects[_teleports[j].index()] = &_teleports[j];
    tiles->putObjectOnTile(_teleports[j].index(), spec.tile1);
    j++;

    assertTrue(numObjects < maxNumObjects);
    _teleports[j].init(numObjects++, spec.tile1, spec.paletteIndex);
    objects[_teleports[j].index()] = &_teleports[j];
    tiles->putObjectOnTile(_teleports[j].index(), spec.tile2);
    j++;
  }
}

void Level::initGaps() {
  for (uint8_t i = 0; i < _levelSpec->numGaps; i++) {
    GapSpec spec = _levelSpec->gapSpecs[i];

    assertTrue(numObjects < maxNumObjects);

    _gaps[i].init(numObjects++, spec.paletteIndex);
    objects[_gaps[i].index()] = &_gaps[i];

    tiles->putObjectOnTile(_gaps[i].index(), spec.pos);
  }
}

void Level::initObjects() {
  numObjects = 0;

  initPickups();
  initTeleports();
  initGaps();
}

void Level::init(const LevelSpec *levelSpec) {
  _levelSpec = levelSpec;

  tiles->init(&_levelSpec->tilesSpec, -64);

  initMovers();
  initObjects();
}

void Level::reset() {
  if (_levelSpec->timeLimitInCycles < 0) {
    // Restore pick-ups
    initObjects();
  }

  tiles->reset();

  // Reset all objects
  for (int8_t i = numObjects; --i >= 0; ) {
    objects[i]->reset();
  }

  for (int8_t i = _levelSpec->numBoxes; --i >= 0; ) {
    _boxes[i].reset();
    tiles->putMoverOnTile(_boxes[i].index(), _levelSpec->boxStartPos[i]);
  }

  _started = false;
  _frozen = false;

  _cyclesRemaining = abs(_levelSpec->timeLimitInCycles);
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
      Mover* mover = movers[i];
      if (!mover->isDestroyed()) {
        mover->update();
      }
    }
  }

  if (!_frozen && --_cyclesRemaining == 0) {
    signalDeath("Timed out");
  }
}

void Level::draw() {
  tiles->draw(_started ? &_player : 0);

  drawTimeBar();
}
