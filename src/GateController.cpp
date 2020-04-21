#include "Log.h"
#include "GateController.h"

GateController::GateController() {}

void GateController::initLeftMotor(
        uint8_t speedPin,
        uint8_t direction1Pin,
        uint8_t direction2Pin,
        uint8_t sensorPin) {
  leftMotor = GateMotor(speedPin, direction1Pin, direction2Pin, sensorPin);
}

void GateController::initRightMotor(
        uint8_t speedPin,
        uint8_t direction1Pin,
        uint8_t direction2Pin,
        uint8_t sensorPin) {
  rightMotor = GateMotor(speedPin, direction1Pin, direction2Pin, sensorPin);
}

void GateController::openGate() {
    serialLog.message("Opening Gate", "Controller");
    currentCommand = 'o';

    leftMotor.openGate(false, 255);
    rightMotor.openGate(false, 255);

    delay(60000); // open gate, wait 60 sec, close gate

    closeGate();
}

void GateController::stopGate() {
  serialLog.message("Stopping Gate", "Controller");
  currentCommand = 's';

  leftMotor.stopGate();
  rightMotor.stopGate();
}

void GateController::closeGate() {
  serialLog.message("Closing Gate", "Controller");
  currentCommand = 'c';

  leftMotor.closeGate(false);
  rightMotor.closeGate(true);
}

//void GateController::triggered() {
//    if(currentCommand == 'o') {
//        stopGate();
//    } else if(currentCommand == 's') {
//        closeGate();
//    } else { // if the gate is closed or in process of closing
//        openGate();
//    }
//}

//void GateController::runCommands() {
//   leftMotor.runCommands();
//   rightMotor.runCommands();
//}

//// any sides can be moving
//bool GateController::isMoving() {
//    return leftMotor.isMoving() || rightMotor.isMoving();
//}
//
//// both sides have to be open
//bool GateController::isOpen() {
//    return leftMotor.isOpen() && rightMotor.isOpen();
//}
//
//// both sides have to be stopped
//bool GateController::isStopped() {
//    return leftMotor.isStopped() && rightMotor.isStopped();
//}
//
//// both sides have to be closed
//bool GateController::isClosed() {
//  return leftMotor.isClosed() && rightMotor.isClosed();
//}
