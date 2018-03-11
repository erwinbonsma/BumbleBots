#include "Waves.h"

Wave::Wave() {
  _amplitude = 1;
  _period = 10 * 3; // ~3 seconds
  _waveLength = 4;
}

DirectionalWave::DirectionalWave(float angle) : Wave() {
  _dcol = cos(angle);
  _drow = sin(angle);
}

float const DirectionalWave::eval(MapPos pos) {
  float d = colOfPos(pos) * _dcol + rowOfPos(pos) * _drow;
  return fastCos(d/_waveLength - gb.frameCount/_period) * _amplitude;
}

ShockWave::ShockWave(MapPos origin) : Wave() {
  _origin = origin;
  _startTime = gb.frameCount;
}

float const ShockWave::eval(MapPos pos) {
  int8_t dcol = colOfPos(pos) - colOfPos(_origin);
  int8_t drow = rowOfPos(pos) - rowOfPos(_origin);
  float sqrDist = dcol*dcol + drow*drow;
  float t = (gb.frameCount - _startTime) / _period - sqrDist / (_waveLength * _waveLength);
  return fastCos(max(0, min(1, t)) - 0.25f) * _amplitude;
}
