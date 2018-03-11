#include "Utils.h"

#ifndef __WAVES_INCLUDED
#define __WAVES_INCLUDED

class Wave {
protected:
  float _amplitude;
  float _period;
  float _waveLength;

public:
  Wave();

  void setAmplitude(float amplitude) { _amplitude = amplitude; }
  void setPeriod(float period) { _period = period; }
  void setWaveLength(float waveLength) { _waveLength = waveLength; }

  virtual float const eval(TilePos pos) = 0;
};

class DirectionalWave : public Wave {
  float _dcol;
  float _drow;
public:
  DirectionalWave(float angle);

  float const eval(TilePos pos);
};

class ShockWave : public Wave {
  TilePos _origin;
  uint16_t _startTime;

public:
  ShockWave(TilePos origin);

  float const eval(TilePos pos);
};

#endif

