#include <Gamebuino-Meta.h>

#include "Palettes.h"
#include "Movers.h"
#include "Map.h"
#include "TileTypes.h"
#include "ImageData.h"
#include "Globals.h"

Player player = Player();

void setup() {
  gb.begin();

  tiles->init(&levelDefs[1]);
  mapTilesImage.setTransparentColor(INDEX_LIGHTBLUE);
  botImage.setTransparentColor(INDEX_BLACK);

  numMovers = 0;
  movers[numMovers++] = &player;
  tiles->addMover(28, numMovers);
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  clockCount++;
  tiles->update();
  for (int8_t i = numMovers; --i >= 0; ) {
    movers[i]->update();
  }

  tiles->draw();

  gb.display.print(gb.frameCount);
}
