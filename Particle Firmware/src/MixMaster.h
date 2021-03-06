#ifndef MixMaster_h
#define MixMaster_h

#include "Particle.h"
#include "AccelStepper.h"
#include "PressureManager.h"
#include "globals.h"
#include "SparkIntervalTimer.h"
#include "PailSensor.h"
#include "LiquidSensor.h"

typedef enum{
  START_IDLE, // 0
  IDLE, // 1
  MIXING_CALCULATIONS, // 2
  MIXING, // 3
  START_AUTO_REVERSE, // 4
  AUTO_REVERSING, // 5
  FLUSHING // 6
} MixerState;

typedef enum{
  Resin,
  Hardener
} MixerChannel;

class mixMaster{
public:
  mixMaster();

  // setup pins and pump configurations
  void init();

  // Updates the mixer state handler (ie. the main "brain" of the mixer)
  //  if _changeState is passed true, update will process if in IDLE or MIXING states
  //  and return it as false when it has processed it.
  bool update(bool _changeState);

  // Get the current state of the mixer
  MixerState getState();

  // returns the currently calculated pump speeds
  uint32_t getPumpSpeed(MixerChannel channel);

  // Puts Mix Master in to FLUSHING state
  //  * Mix Master can only be taken in to FLUSHING state through this function
  //  * The "FLUSHING" mixerState calls updateFlushing() and checks for _changestate
  //  * if _changeState is true while "FLUSHING" Mixer State becomes "START_IDLE"
  //  * startFlushing records the time "FLUSHING" started, "FLUSHING" state checks
  //      if "FLUSHING" has been running for longer than FLUSH_CYCLE_DURATION
  void startFlush();

  void runPumps();

  // Current State of Mix Master
  MixerState mixerState = START_IDLE;

private:
  // Pump objects
  AccelStepper ResinPump;
  AccelStepper HardenerPump;

  // Pump Timer Object
  IntervalTimer pumpUpdater;

  // Priming
  uint8_t numConsecutivePrimes = 0;

  // Pump Control functions
  // Calculate the resinPumpSpeed and hardenerPumpSpeed, enable the pumps, return the time to pump
  uint32_t prepForMixing(uint32_t volume, uint32_t flowRate, uint32_t ratioResin, uint32_t ratioHardener);
  void idlePumps();
  bool runPumpsWithErrorCheck();
  bool checkPumpErrors();
  void enablePumps();
  void disablePumps();
  bool _pumpsEnabledState = false;

  // Pump configuration
  const unsigned int ultimateMaxSpeed = 15000;
  const unsigned int autoReverseSpeed = 4000;

  // Pump Info
  uint32_t resinPumpSpeed = 0; //steps/s
  uint32_t hardenerPumpSpeed = 0; //steps/s

  // FLUSHING States
  enum FlushingState{
    FLUSH_INIT,
    FLUSH_CHECK,
    FLUSH_SETUP_PURGE,
    FLUSH_SETUP_WASH_FORWARD,
    FLUSH_SETUP_WASH_REVERSE,
    FLUSH_RUN_PUMPS,
    FLUSH_PAUSE,
    FLUSH_AIR_CHARGE,
    FLUSH_FINISH_DELAY,
    FLUSH_SIGNAL_COMPLETE,
  } FlushingState;

  enum lastMove {
    FLUSH_PURGE,
    FLUSH_WASH_FORWARD,
    FLUSH_WASH_REVERSE,
  } lastMove;

  // MIXING States
  enum MixingState{
    CHARGING,
    DELAY,
    MIX,
  } MixingState;

  // Flushing Interval Charge Handler
  void intervalCharge();
  enum IntervalChargeState {
    INTERVAL_CHARGE_AIR_ON,
    INTERVAL_CHARGE_AIR_PAUSE,
  } IntervalChargeState;
  uint32_t timeIntervalChargeStarted = 0;
  bool enableIntervalCharge = false;
  uint32_t washCount = 0;
  uint32_t flushCount = 0;
  bool initialPurge = false;

  // Flushing State Machine Handler
  void updateFlushing();

  // ZeroDrip
  bool ZeroDrip(bool runZeroDrip);

  // Utility Functions
  uint32_t RPMtoStepsPerSecond(uint32_t RPM);
  uint32_t calculatePumpSpeed(uint32_t flowRate, uint32_t thisPumpRatio, uint32_t otherPumpRatio, uint32_t stepsPerMl);
  uint32_t calculateTimeForVolume(uint32_t volume, uint16_t flowRate);
  uint32_t calculateAutoReverseSteps(uint32_t thisPumpRatio, uint32_t otherPumpRatio);
  uint32_t totalVolumeToSteps(uint32_t volume, uint32_t stepsPerMl, uint32_t thisRatio, uint32_t otherRatio);
  uint32_t getSpeedFromRPM(uint32_t RPM, uint32_t thisStepsPerMl, uint32_t otherStepsPerMl, uint32_t thisRatio, uint32_t otherRatio);
  uint32_t stepsToMl(uint32_t steps, uint32_t stepsPerMl);
};

extern mixMaster MixMaster;

#endif
