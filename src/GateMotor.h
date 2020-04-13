#ifndef GATEMOTOR_H
#define GATEMOTOR_H

#include "Arduino.h"
#include "../.pio/libdeps/esp32doit-devkit-v1/RunningAverage_ID1322/RunningAverage.h"

class RunningAverage;

class GateMotor {
  private:
    char state = 'u'; // unknown, open, closed

    uint8_t motorSpeedPin;
    uint8_t motorDirectionPin1;
    uint8_t motorDirectionPin2;
    uint8_t motorSensorPin;
    uint16_t motorCurrentZeroValue;
    RunningAverage motorCurrent;

    void calibrateCurrentSensor();
   
  public:
    GateMotor();
    GateMotor(uint8_t speedPin, uint8_t directionPin1, uint8_t directionPin2, uint8_t sensorPin);

    void openGate();
    void closeGate();
    void stopGate();

    bool isMoving();
    bool isOpen();
    bool isStopped();
    bool isClosed();
};

#endif
