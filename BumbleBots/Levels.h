#include <Gamebuino-Meta.h>

#include "Utils.h"
#include "Tiles.h"
#include "Movers.h"
#include "Objects.h"

struct LevelSpec {
  const TilePos playerStartPos;

  const uint8_t numEnemies;
  const TilePos *enemyStartPos;

  const uint8_t numPickups;
  const TilePos *pickupStartPos;

  const TilesSpec tilesSpec;
};

#ifdef TEST_LEVELS
  const uint8_t numLevels = 4;
#else
  const uint8_t numLevels = 2;
#endif
extern const LevelSpec levelSpecs[numLevels];

const uint8_t maxNumEnemies = 6;
const uint8_t maxNumPickups = 13;

//-----------------------------------------------------------------------------
// Level declaration

class Level {
  const LevelSpec *_levelSpec;

  uint8_t _numPickupsCollected;

  Player _player;
  Enemy _enemies[maxNumEnemies];
  Pickup _pickups[maxNumPickups];

public:
  /* Initialises the level based on the given spec.
   *
   * This should be called once when entering a level.
   *
   * Note: This top-level init also invokes reset. This is the exception. Other
   * classes should not do so. They can rely on this class to invoke reset when
   * needed.
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

  /* Invoke to signal that a pick-up has been completed.
   */
  void pickupCollected() { _numPickupsCollected++; }
  bool isCompleted();

  void update();
  void draw();
};

