/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "TileTypes.h"

TileType tileTypes[numTileTypes] = {
  // 0: Basic, fixed, light
  TileType {
    .topImageIndex = 2,
    .topFrameIndex = 0,
    .bottomImageIndex = 3,
    .bottomFrameIndex = 0,

    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 0,
    .flags = 0
  },

  // 1: Basic, normal flexibilty
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 1,
    .bottomFrameIndex = 0,

    .paletteIndex = 4,
    .height0 = 0,
    .flexibility = 2,
    .flags = TILEFLAG_CHECKERED
  },

  // 2: Basic, fixed, checkered
  TileType {
    .topImageIndex = 2,
    .topFrameIndex = 0,
    .bottomImageIndex = 3,
    .bottomFrameIndex = 0,

    .paletteIndex = 4,
    .height0 = 0,
    .flexibility = 0,
    .flags = TILEFLAG_CHECKERED
  },

  // 3: Basic, flexibilty-3
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 1,
    .bottomFrameIndex = 0,

    .paletteIndex = 4,
    .height0 = 0,
    .flexibility = 3,
    .flags = TILEFLAG_CHECKERED
  },

  // 4: Bridge Left
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 4,
    .bottomFrameIndex = 0,

    .paletteIndex = 0,
    .height0 = 8,
    .flexibility = 0,
    .flags = 0
  },

  // 5: Bridge Middle
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 1,
    .bottomFrameIndex = 0,

    .paletteIndex = 0,
    .height0 = 8,
    .flexibility = 0,
    .flags = 0
  },

  // 6: Bridge Right
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 4,
    .bottomFrameIndex = 1,

    .paletteIndex = 0,
    .height0 = 8,
    .flexibility = 0,
    .flags = 0
  },

  // 7: Elevator
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 1,
    .bottomFrameIndex = 0,

    .paletteIndex = 0,
    .height0 = 8,
    .flexibility = 9,
    .flags = 0
  },

  // 8: Pillar, Moving
  TileType {
    .topImageIndex = 5,
    .topFrameIndex = 0,
    .bottomImageIndex = 6,
    .bottomFrameIndex = 0,

    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 3,
    .flags = 0
  },

  // 9: Pillar, Fixed
  TileType {
    .topImageIndex = 5,
    .topFrameIndex = 0,
    .bottomImageIndex = 7,
    .bottomFrameIndex = 0,

    .paletteIndex = 0,
    .height0 = 0,
    .flexibility = 0,
    .flags = 0
  },

  // X: TMP Basic, high flexibilty
  TileType {
    .topImageIndex = 0,
    .topFrameIndex = 0,
    .bottomImageIndex = 1,
    .bottomFrameIndex = 0,

    .paletteIndex = 4,
    .height0 = 0,
    .flexibility = 8,
    .flags = TILEFLAG_CHECKERED
  }
};

ImageInfo tileImageInfo[numTileImages] = {
  // 0
  ImageInfo {
    .dx = 1,
    .dy = 0
  },
  // 1
  ImageInfo {
    .dx = 0,
    .dy = 0
  },
  // 2
  ImageInfo {
    .dx = 2,
    .dy = 0
  },
  // 3
  ImageInfo {
    .dx = 0,
    .dy = 0
  },
  // 4
  ImageInfo {
    .dx = 0,
    .dy = 0
  },
  // 5
  ImageInfo {
    .dx = 3,
    .dy = 2
  },
  // 6
  ImageInfo {
    .dx = 2,
    .dy = 0
  },
  // 7
  ImageInfo {
    .dx = 2,
    .dy = 0
  },
};

const uint8_t data_0[] = {
  13, 4, 1, 0, 0, (uint8_t)INDEX_LIGHTBLUE, 1,
  0xcc, 0xcc, 0xcc, 0x7c, 0xcc, 0xcc, 0xcc,
  0xcc, 0xcc, 0x77, 0x77, 0x7c, 0xcc, 0xcc,
  0xcc, 0x77, 0x77, 0x77, 0x77, 0x7c, 0xcc,
  0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x7c
};

const uint8_t data_1[] = {
  15, 7, 1, 0, 0, 0xFF, 1,
  0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x70,
  0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x75, 0x50,
  0x66, 0x66, 0x77, 0x77, 0x77, 0x75, 0x55, 0x50,
  0x66, 0x66, 0x66, 0x77, 0x75, 0x55, 0x55, 0x50,
  0x00, 0x66, 0x66, 0x66, 0x55, 0x55, 0x50, 0x00,
  0x00, 0x00, 0x66, 0x66, 0x55, 0x50, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x66, 0x50, 0x00, 0x00, 0x00
};

// Note: dx differs compared to data_0, so cannot be merged with current scheme
const uint8_t data_2[] = {
  13, 4, 1, 0, 0, (uint8_t)INDEX_LIGHTBLUE, 1,
  0xcc, 0xcc, 0xcc, 0x7c, 0xcc, 0xcc, 0xcc,
  0xcc, 0xcc, 0x77, 0x77, 0x7c, 0xcc, 0xcc,
  0xcc, 0x77, 0x77, 0x77, 0x77, 0x7c, 0xcc,
  0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x7c
};

const uint8_t data_3[] = {
  16, 10, 1, 0, 0, 0xFF, 1,
  0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
  0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x55,
  0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x55, 0x55,
  0x66, 0x66, 0x67, 0x77, 0x77, 0x55, 0x55, 0x55,
  0x66, 0x66, 0x66, 0x67, 0x55, 0x55, 0x55, 0x55,
  0x66, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x55,
  0x06, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x00,
  0x00, 0x06, 0x66, 0x66, 0x55, 0x55, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x66, 0x55, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00
};

const uint8_t data_4[] = {
  15, 20, 2, 0, 0, 0xFF, 1,
  // Bridge Left
  0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x70,
  0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x75, 0x50,
  0x66, 0x66, 0x77, 0x77, 0x77, 0x75, 0x55, 0x50,
  0x66, 0x66, 0x66, 0x77, 0x75, 0x55, 0x55, 0x50,
  0x66, 0x66, 0x66, 0x66, 0x55, 0x55, 0x50, 0x00,
  0x66, 0x66, 0x66, 0x66, 0x55, 0x50, 0x00, 0x00,
  0x66, 0x66, 0x66, 0x66, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x66, 0x60, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x66, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x66, 0x65, 0x55, 0x50, 0x00, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,
  0x66, 0x55, 0x55, 0x55, 0x50, 0x00, 0x00, 0x00,

  // Bridge Right
  0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x70,
  0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x75, 0x50,
  0x66, 0x66, 0x77, 0x77, 0x77, 0x75, 0x55, 0x50,
  0x66, 0x66, 0x66, 0x77, 0x75, 0x55, 0x55, 0x50,
  0x06, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x06, 0x66, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x66, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x66, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x06, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x06, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50,
  0x00, 0x00, 0x00, 0x66, 0x55, 0x55, 0x55, 0x50
};

const uint8_t data_5[] = {
  11, 2, 1, 0, 1, (uint8_t)INDEX_LIGHTBLUE, 1,
  // Pillar Top
  0xcc, 0xff, 0xff, 0x44, 0x4c, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xf4, 0x4c
};

const uint8_t data_6[] = {
  13, 14, 1, 0, 1, 0xFF, 1,
  // Pillar Bottom
  0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x40,
  0x67, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x56, 0x67, 0x77, 0xff, 0xff, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x06, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x00, 0x06, 0x56, 0x55, 0x55, 0x00, 0x00
};

const uint8_t data_7[] = {
  13, 18, 1, 0, 1, 0xFF, 1,
  // Tall Pillar Bottom
  /* Note: This is the same image as in data_6 but a bit taller. Not using this
   * taller image everywhere to improve performance. In Barsaman level this
   * saves drawing (64 - 3) * 4 image lines.
   */
  0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x40,
  0x67, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x56, 0x67, 0x77, 0xff, 0xff, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x56, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x66, 0x66, 0x56, 0x55, 0x55, 0x00, 0x00,
  0x06, 0x65, 0x65, 0x65, 0x50, 0x50, 0x00,
  0x00, 0x06, 0x56, 0x55, 0x55, 0x00, 0x00
};

Image tileImages[numTileImages] = {
  Image(data_0),
  Image(data_1),
  Image(data_2),
  Image(data_3),
  Image(data_4),
  Image(data_5),
  Image(data_6),
  Image(data_7),
};
