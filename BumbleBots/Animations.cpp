/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Game.h"
#include "Globals.h"
#include "Images.h"

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

const Gamebuino_Meta::Sound_FX dieSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,80,7},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,89,7},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-1,0,100,12},
};

Animation* DieAnimation::init(const char *cause) {
  _cause = cause;
  game.level().freeze();
  gb.sound.fx(dieSfx);

  return Animation::init();
}

Animation* DieAnimation::update() {
  Animation::update();

  if (clock() == 50) {
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
//  gb.display.setColor(INDEX_RED);
//  gb.display.setCursor(0, 56);
//  gb.display.print(_cause);
}

//-----------------------------------------------------------------------------
// GameOverAnimation implementation

const Gamebuino_Meta::Sound_FX gameOverSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,89,12},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,100,12},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-2,0,113,20},
};

Animation* GameOverAnimation::init(bool hiScore) {
  _hiScore = hiScore;

  gb.sound.fx(gameOverSfx);

  return Animation::init();
}

Animation* GameOverAnimation::update() {
  Animation::update();

  if (gb.buttons.held(BUTTON_A, 0)) {
    showStatsScreen();
  }

  return this;
}

void GameOverAnimation::draw() {
  if (!_hiScore || clock() % 32 < 16) {
    gb.display.drawImage(26, 22, gameOverImage);
  }
  else {
    gb.display.drawImage(26, 13, bestGameEverImage);
  }
}

//-----------------------------------------------------------------------------
// GameDoneAnimation declaration

// Sounds as "End of the line"
const Gamebuino_Meta::Sound_FX gameDoneSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,-1,0,50,8},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,-1,0,50,4},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,-1,0,50,4},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-1,0,47,16},
};

Animation* GameDoneAnimation::init() {
  gb.sound.fx(gameDoneSfx);

  return Animation::init();
}

Animation* GameDoneAnimation::update() {
  Animation::update();

  // TODO: Score points for remaining lives

  if (gb.buttons.held(BUTTON_A, 0)) {
    showStatsScreen();
  }

  return this;
}

void GameDoneAnimation::draw() {
  gb.display.drawImage(30, 22, gameDoneImage);
}

//-----------------------------------------------------------------------------
// LevelDoneAnimation implementation

const Gamebuino_Meta::Sound_FX levelDoneSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,89,8},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,71,8},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,-10,63,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,10,63,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,112,-4,-10,63,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,96,-4,10,63,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,80,-4,-10,63,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,64,-8,10,63,4},
};

const Gamebuino_Meta::Sound_FX timeScoreSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-64,0,50,1},
};

Animation* LevelDoneAnimation::init() {
  game.level().freeze();

  gb.sound.fx(levelDoneSfx);

  return Animation::init();
}

Animation* LevelDoneAnimation::update() {
  Animation::update();

  if (clock() == 50) {
    if (game.level().hasTimeLeft()) {
      game.level().decreaseTimeLeft();
      gb.sound.fx(timeScoreSfx);
      game.addToScore(1);
      rewindClock();
    }
  }
  else if (clock() == 60) {
    return game.nextLevel();
  }

  return this;
}

//-----------------------------------------------------------------------------
// LevelStartAnimation implementation

const Gamebuino_Meta::Sound_FX getReadySfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,50,3},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,4,0,0,100,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,47,6},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-2,0,50,7},
};

Animation* LevelStartAnimation::init() {
  game.level().reset();

  return Animation::init();
}

Animation* LevelStartAnimation::update() {
  Animation::update();

  if (clock() == 60 || gb.buttons.held(BUTTON_A, 0)) {
    gb.sound.fx(getReadySfx);

    game.level().start();
    return nullptr;
  }

  return this;
}
