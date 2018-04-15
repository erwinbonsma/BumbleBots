/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Utils.h"
#include "Tiles.h"
#include "Movers.h"
#include "Objects.h"

#ifdef DEVELOPMENT
  #define TEST_LEVELS
#endif

//-----------------------------------------------------------------------------
// LevelTilesSpec declaration

class LevelTilesSpec : public TilesSpec {
  /* 1D array for 2D map
   *
   * bits:
   * 7..5 : height (0..7)
   * 4..0 : tileType (0..31)
   */
  const uint8_t* _tiles;

public:
  LevelTilesSpec(const uint8_t* tiles);

  int8_t baselineHeightAt(TilePos pos) const;

  TileType& tileTypeAt(TilePos pos) const;
};

//-----------------------------------------------------------------------------
// TeleportPairSpec declaration

struct TeleportPairSpec {
  const int8_t tile1;
  const int8_t tile2;
  const uint8_t paletteIndex;
};

//-----------------------------------------------------------------------------
// GapSpec declaration

struct GapSpec {
  const TilePos pos;
  const uint8_t paletteIndex;
};

//-----------------------------------------------------------------------------
// ObstacleSpec declaration

struct ObstacleSpec {
  const TilePos pos;
  const uint8_t typeIndex;
};

//-----------------------------------------------------------------------------
// LevelSpec declaration

struct LevelSpec {
  const char* title;

  const TilePos playerStartPos;

  const uint8_t numEnemies;
  const TilePos* enemyStartPos;

  const uint8_t numPickups;
  const TilePos* pickupStartPos;

  const uint8_t numTeleportPairs;
  const TeleportPairSpec* teleportSpecs;

  const uint8_t numBoxes;
  const TilePos* boxStartPos;

  const uint8_t numGaps;
  const GapSpec* gapSpecs;

  const uint8_t numObstacles;
  const ObstacleSpec* obstacleSpecs;

  // Negative value: Restore pick-ups on level reset
  const int16_t timeLimitInCycles;

  const LevelTilesSpec tilesSpec;
};

#ifdef TEST_LEVELS
  const uint8_t numLevels = 11;
#else
  const uint8_t numLevels = 10;
#endif
extern const LevelSpec levelSpecs[numLevels];

const uint8_t maxNumEnemies = 7;
const uint8_t maxNumPickups = 13;
const uint8_t maxNumTeleports = 8;
const uint8_t maxNumBoxes = 17;
const uint8_t maxNumGaps = 4;
const uint8_t maxNumObstacles = 6;

//-----------------------------------------------------------------------------
// Level declaration

class Level {
  const LevelSpec *_levelSpec;

  bool _started;
  bool _frozen;
  uint8_t _numPickupsCollected;
  int16_t _cyclesRemaining;

  Player _player;
  Enemy _enemies[maxNumEnemies];
  Box _boxes[maxNumBoxes];

  Pickup _pickups[maxNumPickups];
  Teleport _teleports[maxNumTeleports];
  Gap _gaps[maxNumGaps];
  Obstacle _obstacles[maxNumObstacles];

  void drawTimeBar();

  void initPlayer();
  void initEnemies();
  void initBoxes();
  void initMovers();

  void initPickups();
  void initTeleports();
  void initGaps();
  void initObstacles();
  void initObjects();

public:
  bool hasTimeLeft() { return _cyclesRemaining > 0; }
  void decreaseTimeLeft() { _cyclesRemaining -= 25; }

  /* Initialises the level based on the given spec.
   *
   * This should be called once when entering a level.
   */
  void init(const LevelSpec *levelSpec);

  /* Resets the level.
   *
   * It should be called after the player died. It will, for example, put all
   * movers back to their starting position. However, objects remain in the
   * state they were (collected pick-ups are gone, pushed boxes are moved, etc)
   *
   * Note: Some levels are configured to have a hard reset. This can be
   * realized by simply invoking init again.
   */
  void reset();

  /* Start playing. This adds the movers to the level. It should be called
   * (sometime) after reset is called.
   */
  void start();

  /* Stop playing. Movers are frozen.
   */
  void freeze();

  /* Invoke to signal that a pick-up has been completed.
   */
  void pickupCollected() { _numPickupsCollected++; }
  bool isCompleted();

  void update();
  void draw();
};

