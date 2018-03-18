#include "Utils.h"

#ifndef __WAVES_INCLUDED
#define __WAVES_INCLUDED

class Wave {
protected:
  uint8_t _amplitude;
  uint8_t _period;
  uint8_t _waveLength;

public:
  Wave();

  uint8_t period() const { return _period; }
  void setAmplitude(uint8_t amplitude) { _amplitude = amplitude; }
  void setPeriod(uint8_t period) { _period = period; }
  void setWaveLength(uint8_t waveLength) { _waveLength = waveLength; }

  /* Input: t is normalized time, mapped to 0..255 based on period
   * Output: output scaled by 256.
   */
  virtual int16_t const eval(TilePos pos, uint8_t t) = 0;
};

class DirectionalWave : public Wave {
  int16_t _dcol;
  int16_t _drow;
public:
  DirectionalWave(float angle);

  int16_t const eval(TilePos pos, uint8_t t);
};

//class ShockWave : public Wave {
//  TilePos _origin;
//  uint16_t _startTime;
//
//public:
//  ShockWave(TilePos origin);
//
//  float const eval(TilePos pos);
//};

#endif

