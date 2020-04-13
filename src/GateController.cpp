#include "Log.h"
#include "GateController.h"

GateController::GateController() {}

void GateController::initLeftMotor(uint8_t speedPin, uint8_t direction1Pin, uint8_t direction2Pin, uint8_t sensorPin) {
  leftMotor = GateMotor(speedPin, direction1Pin, direction2Pin, sensorPin);
}

void GateController::initRightMotor(uint8_t speedPin, uint8_t direction1Pin, uint8_t direction2Pin, uint8_t sensorPin) {
  rightMotor = GateMotor(speedPin, direction1Pin, direction2Pin, sensorPin);
}

void GateController::openGate(int openPause) {
  serialLog.message("Opening Gate");
  currentCommand = 'o';
  
  leftMotor.openGate();
  rightMotor.openGate();
}

void GateController::stopGate() {
  serialLog.message("Stopping Gate");
  currentCommand = 's';
  
  leftMotor.stopGate();
  rightMotor.stopGate();
}

void GateController::closeGate() {
  serialLog.message("Closing Gate");
  currentCommand = 'c';
  
  leftMotor.closeGate();
  rightMotor.closeGate();
}

// any can be moving
bool GateController::isMoving() {
    return leftMotor.isMoving() || rightMotor.isMoving();
}

// both have to be open
bool GateController::isOpen() {
    return leftMotor.isOpen() && rightMotor.isOpen();
}

// both have to be stopped
bool GateController::isStopped() {
    return leftMotor.isStopped() && rightMotor.isStopped();
}

// both have to be closed
bool GateController::isClosed() {
  return leftMotor.isClosed() && rightMotor.isClosed();
}
