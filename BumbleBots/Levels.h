#include <Gamebuino-Meta.h>

#include "Utils.h"
#include "Tiles.h"
#include "Movers.h"

struct LevelSpec {
  const TilePos playerStartPos;

  const uint8_t numEnemies;
  const TilePos *enemyStartPos;

  const TilesSpec tilesSpec;
};

const uint8_t numLevels = 4;
extern const LevelSpec levelSpecs[numLevels];

const uint8_t maxNumEnemies = 6;

class Level {
  const LevelSpec *_levelSpec;

  Player _player;
  Enemy _enemies[maxNumEnemies];

public:
  void init(const LevelSpec *levelSpec);

  void reset();
  void update();
  void draw();
};

