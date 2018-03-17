#include <Gamebuino-Meta.h>

#include "Palettes.h"
#include "Movers.h"
#include "Tiles.h"
#include "TileTypes.h"
#include "ImageData.h"
#include "Globals.h"

Player player = Player();

const int8_t numEnemies = 4;
Enemy enemies[numEnemies];

uint8_t levelNum = 1;

void resetLevel() {
  tiles->init(&levelSpecs[levelNum]);

  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->reset();
  }

  tiles->putMoverOnTile(player.index(), 28);
  tiles->putMoverOnTile(enemies[0].index(), 0);
  tiles->putMoverOnTile(enemies[1].index(), 7);
  tiles->putMoverOnTile(enemies[2].index(), 56);
  tiles->putMoverOnTile(enemies[3].index(), 63);
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

  for (uint8_t i = 0; i < numEnemies; i++) {
    enemies[i].init(numMovers++, player.index());
    movers[enemies[i].index()] = &enemies[i];
  }

  resetLevel();

  gb.setFrameRate(20);
}

uint8_t frameRate = 20;

void loop() {
  while(!gb.update());
  gb.display.clear();

  if (gb.buttons.held(BUTTON_A, 0)) {
    resetLevel();
    //if (frameRate > 1) {
    //  gb.setFrameRate(--frameRate);
    //}
  }
  if (gb.buttons.held(BUTTON_B, 0)) {
    levelNum = (levelNum + 1 ) % numLevels;
    //gb.setFrameRate(++frameRate);
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
