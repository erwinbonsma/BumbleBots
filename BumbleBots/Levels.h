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

  TileType* tileTypeAt(TilePos pos) const;
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

  // Negative value: Restore pick-ups on level reset
  const int16_t timeLimitInCycles;

  const LevelTilesSpec tilesSpec;
};

#ifdef TEST_LEVELS
  const uint8_t numLevels = 6;
#else
  const uint8_t numLevels = 4;
#endif
extern const LevelSpec levelSpecs[numLevels];

const uint8_t maxNumEnemies = 6;
const uint8_t maxNumPickups = 13;

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
  Pickup _pickups[maxNumPickups];

  void drawTimeBar();

  void initMovers();
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

