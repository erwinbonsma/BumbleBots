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

  tiles->init(&levelSpecs[0]);
  mapTilesImage.setTransparentColor(INDEX_LIGHTBLUE);
  botImage.setTransparentColor(INDEX_BLACK);

  numMovers = 0;
  player.setIndex(numMovers++);
  movers[player.index()] = &player;
  tiles->addMover(28, player.index());

  //enemy.setIndex(numMovers++);
  //movers[enemy.index()] = &enemy;
  //tiles->addMover(9, enemy.index());
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  tiles->update();
  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->update();
  }
  tiles->draw();

  gb.display.print(gb.frameCount);
}
