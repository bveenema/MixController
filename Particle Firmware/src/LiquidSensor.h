#ifndef LIQUID_SENSOR_H
#define LIQUID_SENSOR_H

#include "Particle.h"
#include "config.h"
#include "globals.h"

class liquidSensor{
public:
  liquidSensor();

  // Initiates Pins
  void init(uint8_t pin);

  // Checks Liquid Sensors for presesence
  void update();

  // Returns current state of liquid presence
  bool hasLiquid();

  // Set the time no liquid is detected before error
  void setMaxTimeNoLiquid(uint32_t time);

private:
  bool _hasLiquid = true;
  uint8_t _pin = 0;
  uint32_t _lastRead = 0;
  uint32_t _firstTimeNoLiquid = 0;
  uint32_t _maxTimeNoLiquid = 250;
};

extern liquidSensor ResinLiquidSensor;
extern liquidSensor HardenerLiquidSensor;

#endif
