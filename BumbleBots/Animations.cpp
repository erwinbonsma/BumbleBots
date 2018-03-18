#include <Gamebuino-Meta.h>

#include "Animations.h"

#include "Levels.h"

extern Level level;

//-----------------------------------------------------------------------------
// Animation implementation

void Animation::init() {
  _clock = 0;
}

Animation* Animation::update() {
  _clock++;

  return this;
}

//-----------------------------------------------------------------------------
// DieAnimation implementation

void DieAnimation::init(const char *cause) {
  Animation::init();

  _cause = cause;
}

Animation* DieAnimation::update() {
  Animation::update();

  if (clock() == 80) {
    level.reset();
    return 0;
  }

  return this;
}

void DieAnimation::draw() {
  gb.display.setColor(INDEX_RED);
  gb.display.print(_cause);
  for (uint8_t i = 0; i < clock(); i += 10) {
    gb.display.print(".");
  }
  gb.display.println();
}
