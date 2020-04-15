#ifndef GATEMOTOR_H
#define GATEMOTOR_H

#include "Arduino.h"
#include "../.pio/libdeps/esp32doit-devkit-v1/RunningAverage_ID1322/RunningAverage.h"

class RunningAverage;

class GateMotor {
  private:
    char currentCommand = 'u'; // unknown, open, close, stop
    uint32_t sprintTime = 16000;
    uint32_t sprintTimeToSlowDown = 0;
    uint8_t sprintSpeed = 255;
    uint8_t defaultSpeed = 200;
    uint16_t currentThreshold = 25;
    uint32_t stopTill = 0;

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
    void runCommands();
    float getCurrentSensorValue();

//    bool isMoving();
//    bool isOpen();
//    bool isStopped();
//    bool isClosed();
};

#endif
