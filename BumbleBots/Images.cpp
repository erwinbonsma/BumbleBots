/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Images.h"

const uint8_t botImageData[] = {
  8, 10, 10, 0, 0, (uint8_t)INDEX_BLACK, 1,

  0x00, 0x00, 0xc0, 0x00,
  0x00, 0xcc, 0xcc, 0xc0,
  0xcc, 0xcc, 0xcc, 0xcc,
  0xdc, 0xcc, 0xcc, 0x11,
  0xdd, 0xdc, 0x11, 0x11,
  0x8d, 0xdd, 0x11, 0x1a,
  0xd8, 0x8d, 0x11, 0x11,
  0xdd, 0xd8, 0x81, 0x11,
  0x0d, 0xdd, 0x11, 0x00,
  0x00, 0x0d, 0x00, 0x00,

  0x00, 0x00, 0x0c, 0x00,
  0x00, 0xcc, 0xcc, 0xc0,
  0x0c, 0xcc, 0xcc, 0xcc,
  0x0d, 0xcc, 0xcc, 0xc1,
  0x0d, 0xdc, 0x11, 0x11,
  0x08, 0xd1, 0x11, 0x1a,
  0x0d, 0x81, 0x11, 0x11,
  0x0d, 0xd8, 0x11, 0x11,
  0x00, 0xd1, 0x11, 0x10,
  0x00, 0x01, 0x00, 0x00,

  0x00, 0x00, 0x00, 0x00,
  0x0c, 0xcc, 0xcc, 0xc0,
  0x0c, 0xcc, 0xcc, 0xc0,
  0x0c, 0xcc, 0xcc, 0xc0,
  0x0d, 0x1d, 0x1d, 0x10,
  0x01, 0xd1, 0xd1, 0xd0,
  0x08, 0x1d, 0x1d, 0xa0,
  0x01, 0xd1, 0xd1, 0xd0,
  0x0d, 0x1d, 0x1d, 0x10,
  0x00, 0x00, 0x00, 0x00,

  0x00, 0xc0, 0x00, 0x00,
  0x0c, 0xcc, 0xcc, 0x00,
  0xcc, 0xcc, 0xcc, 0xc0,
  0xdc, 0xcc, 0xcc, 0x10,
  0xdd, 0xdd, 0xc1, 0x10,
  0x8d, 0xdd, 0xd1, 0xa0,
  0xdd, 0xdd, 0xda, 0x10,
  0xdd, 0xdd, 0xa1, 0x10,
  0x0d, 0xdd, 0xd1, 0x00,
  0x00, 0x00, 0xd0, 0x00,

  0x00, 0x0c, 0x00, 0x00,
  0x0c, 0xcc, 0xcc, 0x00,
  0xcc, 0xcc, 0xcc, 0xcc,
  0xdd, 0xcc, 0xcc, 0xc1,
  0xdd, 0xdd, 0xc1, 0x11,
  0x8d, 0xdd, 0x11, 0x1a,
  0xdd, 0xdd, 0x1a, 0xa1,
  0xdd, 0xda, 0xa1, 0x11,
  0x00, 0xdd, 0x11, 0x10,
  0x00, 0x00, 0x10, 0x00,

  0x00, 0x00, 0xc0, 0x00,
  0x00, 0xcc, 0xcc, 0xc0,
  0xcc, 0xcc, 0xcc, 0xcc,
  0xdc, 0xcc, 0xcc, 0x11,
  0xdd, 0xdc, 0x11, 0x11,
  0x8d, 0xdd, 0x11, 0x1a,
  0xdd, 0xdd, 0x1a, 0xa1,
  0xdd, 0xda, 0xa1, 0x11,
  0x0d, 0xdd, 0x11, 0x00,
  0x00, 0x0d, 0x00, 0x00,

  0x00, 0x00, 0x0c, 0x00,
  0x00, 0xcc, 0xcc, 0xc0,
  0x0c, 0xcc, 0xcc, 0xcc,
  0x0d, 0xcc, 0xcc, 0xc1,
  0x0d, 0xdc, 0x11, 0x11,
  0x08, 0xd1, 0x11, 0x1a,
  0x0d, 0xa1, 0xaa, 0xa1,
  0x0d, 0xda, 0x11, 0x11,
  0x00, 0xd1, 0x11, 0x10,
  0x00, 0x01, 0x00, 0x00,

  0x00, 0x00, 0x00, 0x00,
  0x0c, 0xcc, 0xcc, 0xc0,
  0x0c, 0xcc, 0xcc, 0xc0,
  0x0c, 0xcc, 0xcc, 0xc0,
  0x0d, 0x1d, 0x1d, 0x10,
  0x01, 0xd1, 0xd1, 0xd0,
  0x0a, 0xaa, 0xaa, 0xa0,
  0x0d, 0x1d, 0x1d, 0x10,
  0x01, 0xd1, 0xd1, 0xd0,
  0x00, 0x00, 0x00, 0x00,

  0x00, 0xc0, 0x00, 0x00,
  0x0c, 0xcc, 0xcc, 0x00,
  0xcc, 0xcc, 0xcc, 0xc0,
  0xdc, 0xcc, 0xcc, 0x10,
  0xdd, 0xdd, 0xc1, 0x10,
  0xad, 0xdd, 0xd1, 0x80,
  0xda, 0xaa, 0xda, 0x10,
  0xdd, 0xdd, 0xa1, 0x10,
  0x0d, 0xdd, 0xd1, 0x00,
  0x00, 0x00, 0xd0, 0x00,

  0x00, 0x0c, 0x00, 0x00,
  0x0c, 0xcc, 0xcc, 0x00,
  0xcc, 0xcc, 0xcc, 0xcc,
  0xdd, 0xcc, 0xcc, 0xc1,
  0xdd, 0xdd, 0xc1, 0x11,
  0xad, 0xdd, 0x11, 0x18,
  0xda, 0xad, 0x11, 0x11,
  0xdd, 0xda, 0xa1, 0x11,
  0x00, 0xdd, 0x11, 0x10,
  0x00, 0x00, 0x10, 0x00
};
Image botImage = Image(botImageData);

const uint8_t dazedData[] = {
  4, 3, 2, 0, 2, (uint8_t)INDEX_BLACK, 1,
  0x00, 0x90,
  0x09, 0x00,
  0x00, 0x09,

  0x00, 0x09,
  0x90, 0x00,
  0x00, 0x90
};
Image dazedImage = Image(dazedData);

const uint8_t pickupData[] = {
  8, 8, 1, 0, 1, (uint8_t)INDEX_BLACK, 1,
  0x00, 0x99, 0x99, 0x00,
  0x09, 0xa9, 0x99, 0x90,
  0x9a, 0xaa, 0x99, 0x94,
  0x99, 0xa9, 0x99, 0x94,
  0x99, 0x99, 0x99, 0x44,
  0x49, 0x99, 0x94, 0x44,
  0x04, 0x44, 0x44, 0x40,
  0x00, 0x44, 0x44, 0x00
};
Image pickupImage = Image(pickupData);

const uint8_t liveIconData[] = {
  4, 6, 1, 0, 1, (uint8_t)INDEX_BLACK, 1,
  0x0c, 0xc0,
  0xcc, 0xcc,
  0xdc, 0xc1,
  0xdd, 0x11,
  0xdd, 0x11,
  0x0d, 0x10
};
Image liveIconImage = Image(liveIconData);

const uint8_t gameOverData[] = {
  29, 19, 1, 0, 1, (uint8_t)INDEX_BLACK, 1,
  0x00, 0x11, 0x11, 0x00, 0x01, 0x11, 0x00, 0x11, 0x11, 0x11, 0x10, 0x01, 0x11, 0x11, 0x00,
  0x01, 0xcc, 0xcc, 0x10, 0x1c, 0xcc, 0x11, 0xcc, 0xcc, 0xcc, 0xc1, 0x1c, 0xcc, 0xcc, 0x10,
  0x1c, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0x10,
  0x1c, 0xc1, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0x11, 0x00,
  0x1c, 0xc1, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xc1, 0x00,
  0x1c, 0xc1, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xc1, 0x00,
  0x1c, 0xc1, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0x11, 0x00,
  0x1c, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xcc, 0x10,
  0x00, 0x11, 0x11, 0x00, 0x11, 0x01, 0x10, 0x11, 0x11, 0x10, 0x11, 0x11, 0x11, 0x11, 0x00,
  0x00, 0x1c, 0xcc, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0x11, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0x11, 0xcc, 0xcc, 0x11, 0xcc, 0x10,
  0x01, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0x11, 0xcc, 0xcc, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0x1c, 0xc1, 0x1c, 0xcc, 0x11, 0xcc, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0x11, 0x00,
  0x01, 0xcc, 0xcc, 0xc1, 0x1c, 0xcc, 0x11, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x10,
  0x00, 0x1c, 0xcc, 0x10, 0x01, 0xc1, 0x01, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x10,
  0x00, 0x01, 0x11, 0x00, 0x01, 0x10, 0x00, 0x11, 0x11, 0x10, 0x11, 0x01, 0x10, 0x11, 0x00
};
Image gameOverImage = Image(gameOverData);

const uint8_t bestGameEverData[] = {
  29, 28, 1, 0, 1, (uint8_t)INDEX_BLACK, 1,
  0x00, 0x01, 0x11, 0x10, 0x01, 0x11, 0x11, 0x00, 0x11, 0x11, 0x01, 0x11, 0x11, 0x10, 0x00,
  0x00, 0x1c, 0xcc, 0xc1, 0x1c, 0xcc, 0xcc, 0x11, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0xc1, 0x00,
  0x00, 0x1c, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0xc1, 0x00,
  0x00, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0x11, 0x1c, 0xc1, 0x11, 0x01, 0x1c, 0xc1, 0x10, 0x00,
  0x00, 0x1c, 0xcc, 0xc1, 0x1c, 0xcc, 0xc1, 0x1c, 0xcc, 0xc1, 0x00, 0x1c, 0xc1, 0x00, 0x00,
  0x00, 0x1c, 0xcc, 0xc1, 0x1c, 0xcc, 0xc1, 0x01, 0xcc, 0xcc, 0x10, 0x1c, 0xc1, 0x00, 0x00,
  0x00, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0x11, 0x01, 0x11, 0xcc, 0x10, 0x1c, 0xc1, 0x00, 0x00,
  0x00, 0x1c, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0x10, 0x1c, 0xc1, 0x00, 0x00,
  0x00, 0x1c, 0xcc, 0xc1, 0x1c, 0xcc, 0xcc, 0x1c, 0xcc, 0xc1, 0x00, 0x1c, 0xc1, 0x00, 0x00,
  0x00, 0x11, 0x11, 0x10, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x01, 0x11, 0x11, 0x00,
  0x01, 0xcc, 0xcc, 0x10, 0x1c, 0xcc, 0x11, 0xcc, 0xcc, 0xcc, 0xc1, 0x1c, 0xcc, 0xcc, 0x10,
  0x1c, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0xcc, 0xcc, 0x1c, 0xcc, 0xcc, 0x10,
  0x1c, 0xc1, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0x11, 0x00,
  0x1c, 0xc1, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xc1, 0x00,
  0x1c, 0xc1, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xc1, 0x00,
  0x1c, 0xc1, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0x11, 0x00,
  0x1c, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x1c, 0xcc, 0xcc, 0x10,
  0x00, 0x11, 0x11, 0x10, 0x11, 0x01, 0x10, 0x11, 0x11, 0x10, 0x11, 0x11, 0x11, 0x11, 0x00,
  0x01, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0x11, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0xcc, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0x11, 0xcc, 0xcc, 0x11, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0x11, 0xcc, 0x1c, 0xc1, 0xcc, 0xcc, 0x11, 0xcc, 0xcc, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0x11, 0x11, 0x1c, 0xcc, 0x11, 0xcc, 0x11, 0x11, 0xcc, 0x1c, 0xc1, 0x11, 0x00,
  0x01, 0xcc, 0xcc, 0xc1, 0x1c, 0xcc, 0x11, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x10,
  0x01, 0xcc, 0xcc, 0xc1, 0x01, 0xc1, 0x01, 0xcc, 0xcc, 0xc1, 0xcc, 0x1c, 0xc1, 0xcc, 0x10,
  0x00, 0x11, 0x11, 0x10, 0x01, 0x10, 0x00, 0x11, 0x11, 0x10, 0x11, 0x01, 0x10, 0x11, 0x00
};
Image bestGameEverImage = Image(bestGameEverData);
