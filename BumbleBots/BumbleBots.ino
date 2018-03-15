#include <Gamebuino-Meta.h>

#include "Palettes.h"
#include "Movers.h"
#include "Tiles.h"
#include "TileTypes.h"
#include "ImageData.h"
#include "Globals.h"

Player player = Player();
Enemy enemy = Enemy();

uint8_t levelNum = 0;

void resetLevel() {
  tiles->init(&levelSpecs[levelNum]);

  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->reset();
  }

  tiles->addMover(28, player.index());
  tiles->addMover(7, enemy.index());
}

void setup() {
  gb.begin();

  botImage.setTransparentColor(INDEX_BLACK);
  dazedImage.setTransparentColor(INDEX_BLACK);
  for (uint8_t i = 0; i < numTileImages; i++) {
    if (tileImageInfo[i].transparentColor != NO_TRANSPARANCY) {
      tileImages[i].setTransparentColor(tileImageInfo[i].transparentColor);
    }
  }

  numMovers = 0;
  player.init(numMovers++);
  movers[player.index()] = &player;

  enemy.init(numMovers++, player.index());
  movers[enemy.index()] = &enemy;

  resetLevel();

  gb.setFrameRate(20);
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  if (gb.buttons.held(BUTTON_A, 0)) {
    resetLevel();
  }
  if (gb.buttons.held(BUTTON_B, 0)) {
    levelNum = (levelNum + 1 ) % numLevels;
  }

  tiles->update();
  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->update();
  }
  tiles->draw();

  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.printf("%d", cpuLoad);
}
