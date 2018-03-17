#include "Waves.h"

Wave::Wave() {
  _amplitude = 1;
  _period = 64; // ~3 seconds
  _waveLength = 4;
}

//DirectionalWave::DirectionalWave(float angle) : Wave() {
//  _dcol = cos(angle);
//  _drow = sin(angle);
//}
//
//float const DirectionalWave::eval(TilePos pos) {
//  float d = colOfPos(pos) * _dcol + rowOfPos(pos) * _drow;
//  return fastCos(d/_waveLength - gb.frameCount/_period) * _amplitude;
//}

DirectionalWave::DirectionalWave(float angle) : Wave() {
  int16_t intAngle = (int16_t)(256 * angle / (2 * PI));
  _dcol = fastCos(intAngle);
  _drow = fastCos(intAngle - 64);
}

int16_t const DirectionalWave::eval(TilePos pos, uint8_t t) {
  int16_t d = colOfPos(pos) * _dcol + rowOfPos(pos) * _drow;
  return fastCos(d/_waveLength - t) * _amplitude;
}

//ShockWave::ShockWave(TilePos origin) : Wave() {
//  _origin = origin;
//  _startTime = gb.frameCount;
//}
//
//float const ShockWave::eval(TilePos pos) {
//  int8_t dcol = colOfPos(pos) - colOfPos(_origin);
//  int8_t drow = rowOfPos(pos) - rowOfPos(_origin);
//  float sqrDist = dcol*dcol + drow*drow;
//  float t = (gb.frameCount - _startTime) / _period - sqrDist / (_waveLength * _waveLength);
//  return fastCos(max(0, min(1, t)) - 0.25f) * _amplitude;
//}
