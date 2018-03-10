#include "Waves.h"

Wave::Wave() {
  _amplitude = 1;
  _period = 25 * 3; // 3 seconds
  _waveLength = 4;
}

DirectionalWave::DirectionalWave(float angle) : Wave() {
  _dcol = cos(angle);
  _drow = sin(angle);
}

float const DirectionalWave::eval(MapPos pos) {
  float d = pos.col * _dcol + pos.row * _drow;
  return sin(2 * PI * (d/_waveLength - clockCount/_period)) * _amplitude;
}

ShockWave::ShockWave(MapPos origin) : Wave() {
  _origin = origin;
  _clock0 = clockCount;
}

float const ShockWave::eval(MapPos pos) {
  int8_t dcol = pos.col - _origin.col;
  int8_t drow = pos.row - _origin.row;
  float dist = sqrt(dcol*dcol + drow*drow);
  float t = (clockCount - _clock0) / _period - dist / _waveLength;
  return sin(2 * PI * max(0, min(1, t))) * _amplitude;
}
