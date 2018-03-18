
const uint8_t maxNumMovers = 8;
const uint8_t maxNumObjects = 16;

#define EMULATION_SETTINGS

// Implemented in Movers.cpp
class Mover;
extern uint8_t numMovers;
extern Mover* movers[maxNumMovers];

// Implemented in Objects.cpp
class Object;
extern uint8_t numObjects;
extern Object* objects[maxNumObjects];

// Implemented in Tiles.cpp
class Tiles;
extern Tiles *const tiles;

// Implemented in main
void signalDeath(const char* cause);
void signalPickupCollected();
void nextLevel();
