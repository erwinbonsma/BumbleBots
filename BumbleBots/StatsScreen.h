/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Utils.h"

//-----------------------------------------------------------------------------
// StatsScreen declaration

class StatsScreen : public LoopHandler {
  uint16_t _animCount;

  void drawValue(uint16_t value, bool improved);

public:
  void reset();

  void update();
  void draw();
};
