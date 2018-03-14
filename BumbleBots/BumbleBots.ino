#include <Gamebuino-Meta.h>

#include "Palettes.h"
#include "Movers.h"
#include "Tiles.h"
#include "TileTypes.h"
#include "ImageData.h"
#include "Globals.h"

Player player = Player();
Enemy enemy = Enemy();

void setup() {
  gb.begin();

  tiles->init(&levelSpecs[1]);

  botImage.setTransparentColor(INDEX_BLACK);
  dazedImage.setTransparentColor(INDEX_BLACK);
  for (uint8_t i = 0; i < numTileImages; i++) {
    if (tileImageInfo[i].transparentColor != NO_TRANSPARANCY) {
      tileImages[i].setTransparentColor(tileImageInfo[i].transparentColor);
    }
  }

  numMovers = 0;
  player.setIndex(numMovers++);
  movers[player.index()] = &player;
  tiles->addMover(28, player.index());

  //enemy.setIndex(numMovers++);
  //movers[enemy.index()] = &enemy;
  //tiles->addMover(9, enemy.index());

  gb.setFrameRate(20);
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  tiles->update();
  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->update();
  }
  tiles->draw();

  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.printf("%d", cpuLoad);
}
