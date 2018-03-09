#include <Gamebuino-Meta.h>

enum Heading {
  NORTH_EAST = 0,
  SOUTH_EAST = 1,
  SOUTH_WEST = 2,
  NORTH_WEST = 3
};

// column Delta for heading
extern const int8_t colDelta[];

// row Delta for heading
extern const int8_t rowDelta[];

extern uint16_t clockCount;
