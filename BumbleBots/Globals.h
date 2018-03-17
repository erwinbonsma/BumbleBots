
const uint8_t maxNumMovers = 8;

// Implemented in Movers.cpp
class Mover;
extern uint8_t numMovers;
extern Mover* movers[maxNumMovers];

// Implemented in Tiles.cpp
class Tiles;
extern Tiles *const tiles;

// Implemented in main
void signalDeath(const char* cause);
