#include "GateMotor.h"
#include "Log.h"

GateMotor::GateMotor() : motorCurrent(25) {}

GateMotor::GateMotor(uint8_t speedPin, uint8_t directionPin1, uint8_t directionPin2, uint8_t sensorPin)
  : motorCurrent(25) {
  motorSpeedPin = speedPin;
  motorDirectionPin1 = directionPin1;
  motorDirectionPin2 = directionPin2;
  motorSensorPin = sensorPin;

  pinMode(speedPin, OUTPUT);
  pinMode(directionPin1, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  pinMode(sensorPin, INPUT);

  calibrateCurrentSensor();
}

void GateMotor::openGate() {
  
}

void GateMotor::closeGate() {
  
}

void GateMotor::stopGate() {
  
}

bool GateMotor::isMoving() {
  return false;
}

bool GateMotor::isOpen() {
  return false;
}

bool GateMotor::isStopped() {
  return false;
}

bool GateMotor::isClosed() {
  return false;
}

void GateMotor::calibrateCurrentSensor() {
  uint16_t total = 0;
  
  for (int i = 0; i < 10; i++) {
    delay(20);
    total += (analogRead(motorSensorPin));
  }

  motorCurrentZeroValue = total / 10;
  serialLog.message(&"Calibrated Current Sensor Zero: "[motorCurrentZeroValue]);
  motorCurrent.fillValue(0, 50);
}
