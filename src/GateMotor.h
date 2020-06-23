#ifndef GATEMOTOR_H
#define GATEMOTOR_H

#include "Arduino.h"

class GateMotor {
  private:
    char currentCommand = 'u'; // unknown, open, close, stop
    uint32_t sprintTime = 16000;
    uint32_t sprintTimeToSlowDown = 0;
    uint8_t sprintSpeed = 255;
    uint8_t defaultSpeed = 200;
    uint16_t currentThreshold = 15;
    uint32_t stopTill = 0;

    uint8_t motorSpeedPin;
    uint8_t motorDirectionPin1;
    uint8_t motorDirectionPin2;
    uint8_t motorSensorPin;
    uint16_t motorCurrentZeroValue;

    void calibrateCurrentSensor();
   
  public:
    GateMotor();
    GateMotor(uint8_t speedPin, uint8_t directionPin1, uint8_t directionPin2, uint8_t sensorPin);

    void openGate(bool block = false, int speed = 255);
    void closeGate(bool block = false, int speed = 255);
    void stopGate();
    float getCurrentSensorValue();
    void blockTillMotorStops();

//    void runCommands();
//    bool isMoving();
//    bool isOpen();
//    bool isStopped();
//    bool isClosed();

};

#endif
