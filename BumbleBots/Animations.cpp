#include <Gamebuino-Meta.h>

#include "Game.h"
#include "Globals.h"

extern Level level;
extern uint8_t levelNum;

//-----------------------------------------------------------------------------
// Animation implementation

Animation* Animation::init() {
  _clock = 0;

  return this;
}

Animation* Animation::update() {
  _clock++;

  return this;
}

//-----------------------------------------------------------------------------
// DieAnimation implementation

Animation* DieAnimation::init(const char *cause) {
  _cause = cause;
  game.level()->freeze();

  return Animation::init();
}

Animation* DieAnimation::update() {
  Animation::update();

  if (clock() == 60) {
    if (game.numLives() >= 0) {
      return game.restartLevel();
    }
    else {
      return game.gameOver();
    }
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

//-----------------------------------------------------------------------------
// GameOverAnimation implementation

Animation* GameOverAnimation::update() {
  Animation::update();

  if (clock() == 50) {
    return game.init();
  }

  return this;
}

void GameOverAnimation::draw() {
  gb.display.setColor(INDEX_RED);
  gb.display.print("GAME OVER");
}

//-----------------------------------------------------------------------------
// LevelDoneAnimation implementation

Animation* LevelDoneAnimation::init() {
  game.level()->freeze();

  return Animation::init();
}

Animation* LevelDoneAnimation::update() {
  Animation::update();

  if (clock() == 80) {
    return game.nextLevel();
  }

  return this;
}

void LevelDoneAnimation::draw() {
  gb.display.setColor(INDEX_GREEN);
  gb.display.println("Level completed!");
}

//-----------------------------------------------------------------------------
// LevelStartAnimation implementation

Animation* LevelStartAnimation::init() {
  game.level()->reset();

  return Animation::init();
}

Animation* LevelStartAnimation::update() {
  Animation::update();

  if (clock() == 80 || gb.buttons.held(BUTTON_A, 0)) {
    game.level()->start();
    return 0;
  }

  return this;
}

void LevelStartAnimation::draw() {
  gb.display.setColor(INDEX_LIGHTBLUE);
  gb.display.printf("Level %d\n", game.levelNum());
  if (clock() > 50) {
    gb.display.println("Ready to bumble?");
  }
}
