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

Animation* GameOverAnimation::init() {
  _hiScore = game.registerGameScore();

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

/* Light color gradients.
 *
 * These vary from Red to Green to Blue to Red. The gradients have been created
 * using http://www.perbang.dk/rgbgradient/ with 13 steps between each primary
 * color.
 *
 * This resulted in the following RGB colors:
 *   0xff0000, 0xff2a00, 0xff5500, 0xff7f00, 0xffaa00, 0xffd400,
 *   0xffff00, 0xd4ff00, 0xa9ff00, 0x7fff00, 0x54ff00, 0x2aff00,
 *   0x00ff00, 0x00ff2a, 0x00ff55, 0x00ff7f, 0x00ffa9, 0x00ffd4,
 *   0x00ffff, 0x00d4ff, 0x00a9ff, 0x007fff, 0x0054ff, 0x002aff,
 *   0x0000ff, 0x2a00ff, 0x5400ff, 0x7f00ff, 0xaa00ff, 0xd400ff,
 *   0xff00ff, 0xff00d4, 0xff00aa, 0xff007f, 0xff0055, 0xff002a
 *
 * These have been programmatically converted using gb.createColor to the array
 * with RGB565 values below.
 */
const uint8_t numGradientColors = 36;
const uint16_t gradientColors[numGradientColors] = {
  0xf800, 0xf940, 0xfaa0, 0xfbe0, 0xfd40, 0xfea0,
  0xffe0, 0xd7e0, 0xafe0, 0x7fe0, 0x57e0, 0x2fe0,
  0x07e0, 0x07e5, 0x07ea, 0x07ef, 0x07f5, 0x07fa,
  0x07ff, 0x06bf, 0x055f, 0x03ff, 0x02bf, 0x015f,
  0x001f, 0x281f, 0x501f, 0x781f, 0xa81f, 0xd01f,
  0xf81f, 0xf81a, 0xf815, 0xf80f, 0xf80a, 0xf805,
};

const Gamebuino_Meta::Sound_FX liveScoreSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-64,0,50,1},
};

Animation* GameDoneAnimation::init() {
  gb.sound.fx(gameDoneSfx);

  return Animation::init();
}

Animation* GameDoneAnimation::update() {
  Animation::update();

  if (clock() == 50) {
    if (game.numLives() > 0) {
      game.removeLive();
    }
    else {
      setClock(120);
    }
  }

  if (clock() == 120) {
    if (game.numLives() > 0) {
      setClock(45);
    }
    else {
      game.registerGameScore();
    }
  }

  if (clock() > 120) {
    rewindClock(); // Prevent overflow

    if (gb.buttons.held(BUTTON_A, 0)) {
      showStatsScreen();
    }
  }

  return this;
}

/* Lights animation.
 *
 * Two "chains" of 4-lights circle the console clockwise. The chains are both
 * a single color which continuously changes. Both chain colors are always at
 * opposite ends of the color gradient.
 */
void GameDoneAnimation::drawLights() {
  // Vary color of chains over time
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t x = (i < 4) ? 0 : 1;
    uint8_t y = (i < 4) ? i : 7 - i;
    // The "chain" that is currently occupying this light-pixel
    uint8_t chain = ((i + gb.frameCount / 2) / 4) % 2;
    uint8_t chainColorIndex =
      (gb.frameCount / 4 + chain * (numGradientColors / 2)) % numGradientColors;
    gb.lights.drawPixel(x, y, (Color)gradientColors[chainColorIndex]);
  }
}

void GameDoneAnimation::draw() {
  if (clock() >= 50 && clock() < 120) {
    gb.sound.fx(liveScoreSfx);
    game.addToScore(1);
    gb.display.drawImage(10 + clock() - 50, 1, liveIconImage);
  }

  gb.display.drawImage(18, 22, gameDoneImage);

  drawLights();
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

const Gamebuino_Meta::Sound_FX* timeScoreSfx = liveScoreSfx;

Animation* LevelDoneAnimation::init() {
  game.level().freeze();

  _levelHi = false;

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
    else {
      _levelHi = game.registerLevelScore();
    }
  }
  else if (clock() == (_levelHi ? 200 : 60)) {
    return game.nextLevel();
  }

  return this;
}

void LevelDoneAnimation::draw() {
  if (_levelHi) {
    gb.display.drawImage(24, 18, levelHiImage);
  }
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
