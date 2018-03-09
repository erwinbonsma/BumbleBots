#include "Map.h"

class Wave {
protected:
  float _amplitude;
  float _period;
  float _waveLength;

public:
  void setAmplitude(float amplitude) { _amplitude = amplitude; }
  void setPeriod(float period) { _period = period; }
  void setWaveLength(float waveLength) { _waveLength = waveLength; }

  virtual float const eval(MapPos pos) = 0;
};

class DirectionalWave : Wave {
  float _dcol;
  float _drow;
public:
  DirectionalWave(float angle);

  float const eval(MapPos pos);
};

class ShockWave : Wave {
  MapPos _origin;
  uint16_t _clock0;

public:
  ShockWave(MapPos origin);

  float const eval(MapPos pos);
};

