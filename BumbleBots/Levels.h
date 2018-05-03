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
  const ObstacleType type;
};

//-----------------------------------------------------------------------------
// BoxSpec declaration

struct BoxSpec {
  const TilePos pos;
  const BoxType type;
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
  const BoxSpec* boxSpecs;

  const uint8_t numGaps;
  const GapSpec* gapSpecs;

  const uint8_t numObstacles;
  const ObstacleSpec* obstacleSpecs;

  // Negative value: Restore pick-ups on level reset
  const int16_t timeLimitInCycles;

  const LevelTilesSpec tilesSpec;
};

const uint8_t numLevels = 16;
extern const LevelSpec levelSpecs[numLevels];

const uint8_t maxNumEnemies = 7;
const uint8_t maxNumPickups = 13;
const uint8_t maxNumTeleports = 8;
const uint8_t maxNumBoxes = 18;
const uint8_t maxNumGaps = 6;
const uint8_t maxNumObstacles = 8;

//-----------------------------------------------------------------------------
// Level declaration

class Level {
  const LevelSpec *_levelSpec;

  bool _started;
  bool _frozen;
  int8_t _numPickupsCollected;
  int8_t _numBoxesToDestroy;
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

  void resetBoxes();

public:
  bool hasTimeLeft() { return _cyclesRemaining > 0; }
  void decreaseTimeLeft() { _cyclesRemaining -= 25; }

  /* Initialises the level based on the given spec.
   *
   * This should be called once when entering a level.
   */
  void init(const LevelSpec *levelSpec);

  /* Indicates if a reset restores the level back to its original state.
   *
   * When true, all pick-ups are restored. If false, collected pick-ups are
   * not respawned.
   */
  bool resetsFully();

  /* Resets the level.
   *
   * It should be called after the player died. It will, for example, put all
   * movers back to their starting position. Depending on how the level is
   * configured pick-ups may also respawn.
   */
  void reset();

  /* Start playing. This adds the movers to the level. It should be called
   * (sometime) after reset is called.
   */
  void start();

  /* Stop playing. Movers are frozen.
   */
  void freeze();

  /* Invoke to signal that a pick-up has been collected.
   */
  void pickupCollected() { _numPickupsCollected++; }
  /* Invoke to signal that a box which must be destroyed has been destroyed.
   */
  void boxDestroyed() { _numBoxesToDestroy--; }
  bool isCompleted();

  void update();
  void draw();
};

