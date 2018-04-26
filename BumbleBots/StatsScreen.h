/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Utils.h"

//-----------------------------------------------------------------------------
// StatsScreen declaration

class StatsScreen : public LoopHandler {
  uint8_t _levelRun;
  uint16_t _score;
  uint16_t _animCount;

public:
  void init(uint8_t levelRun, uint16_t score);

  void update();
  void draw();
};
