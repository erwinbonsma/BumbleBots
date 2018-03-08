#include <Gamebuino-Meta.h>

#include "Palettes.h"
#include "Movers.h"

Player player = Player();
Enemy enemy = Enemy();

void setup() {
  gb.begin();

  initPalettes();
}

void loop() {
  while(!gb.update());

  gb.display.clear();

  player.update();
  player.draw(36, 37);
  enemy.draw(50, 37);
}
