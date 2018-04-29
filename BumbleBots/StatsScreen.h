/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Utils.h"

//-----------------------------------------------------------------------------
// StatsScreen declaration

const uint8_t numLights = 8;

class StatsScreen : public LoopHandler {
  uint16_t _animCount;

  // The absolute value is its intensity. Sign indicates direction of change.
  int8_t _lightState[numLights];

  void updateLights();

  void drawLights();
  void drawValue(uint16_t value, bool improved);

public:
  void reset();

  void update();
  void draw();
};
