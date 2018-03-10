#include <Gamebuino-Meta.h>

#include "Palettes.h"
#include "Movers.h"
#include "Map.h"
#include "TileTypes.h"
#include "ImageData.h"

Player player = Player();
Enemy enemy = Enemy();
Map tiles = Map();

void setup() {
  gb.begin();

  initPalettes();

  tiles.init(&levelDefs[1]);
  mapTilesImage.setTransparentColor(INDEX_LIGHTBLUE);
  botImage.setTransparentColor(INDEX_BLACK);
}

void loop() {
  while(!gb.update());

  gb.display.clear();

  clockCount++;
  tiles.update();
  player.update();

  tiles.draw();
  player.draw(36, 37);
  //enemy.draw(50, 37);

  gb.display.print(gb.frameCount);
}
