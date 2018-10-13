#ifndef PressureManager_H
#define PressureManager_H

#include "Particle.h"
#include "config.h"

class pressureManager{
public:
  // Constructor: takes targetPressure (milli-inH20) agrument - defaults to 10 inH20
  pressureManager(){}

  // Initialize air pump and pressure sensor
  void init(uint32_t targetPressure = defaultSettings.chargePressure);

  // Charge the Pails to the target pressure if isCharging is true
  void update();

  // Function to set whether pails should be charged (true) or not (false)
  void setChargingState(bool charge);

  // Returns True if Pails are charged
  bool isCharged();

  int32_t updateTargetPressure(int32_t _targetPressure);

  int32_t getPressure();
private:
  // True if Pails are charged
  bool charged = false;

  // True if pails should be charged
  bool isCharging = false;

  // Pressure to Maintain in the Pails
  int32_t targetPressure = 0; // milli-inH20

  // Pressure Container
  struct{
    int32_t current = 0;
    uint16_t samples[100] = {0};
    uint8_t index = 0;
    uint8_t length = 100;
    bool isValid = false;
    uint32_t lastRead = 0;
    uint16_t accumulateUnderPressure = 0;
  } pressure;

  // Reads the pressure sensor and returns the value in milli-inH2O
  uint16_t readPressure();
};

extern pressureManager PressureManager;

#endif
