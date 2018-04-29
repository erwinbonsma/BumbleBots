/*
 * Bumble Bots, a Gamebuino game
 *
 * Copyright 2018, Erwin Bonsma
 */

#include "Waves.h"

Wave::Wave() {
  _amplitude = 1;
  _period = 80; // ~3 seconds
  _waveLength = 4;
}

DirectionalWave::DirectionalWave(float angle) : Wave() {
  int16_t intAngle = (int16_t)(256 * angle / (2 * PI));
  _dcol = fastCos(intAngle);
  _drow = fastCos(intAngle - 64);
}

int16_t DirectionalWave::eval(TilePos pos, uint8_t t) const {
  int16_t d = colOfPos(pos) * _dcol + rowOfPos(pos) * _drow;
  return fastCos(d/_waveLength - t) * _amplitude;
}
