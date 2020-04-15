#include "GateMotor.h"
#include "Log.h"
#include "../.pio/libdeps/esp32doit-devkit-v1/ESP32 AnalogWrite_ID5819/src/analogWrite.h"

GateMotor::GateMotor() : motorCurrent(25) {}

GateMotor::GateMotor(
        uint8_t speedPin,
        uint8_t directionPin1,
        uint8_t directionPin2,
        uint8_t sensorPin) : motorCurrent(25) {

  motorSpeedPin = speedPin;
  motorDirectionPin1 = directionPin1;
  motorDirectionPin2 = directionPin2;
  motorSensorPin = sensorPin;

  pinMode(speedPin, OUTPUT);
  pinMode(directionPin1, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  pinMode(sensorPin, INPUT);

  analogWrite(motorSpeedPin, defaultSpeed);

  calibrateCurrentSensor();
}

void GateMotor::openGate() {
    serialLog.message("Open Gate", "Motor");
    currentCommand = 'o';
    digitalWrite(motorDirectionPin1, true);
    digitalWrite(motorDirectionPin2, false);

//    serialLog.message("analogWrite", "Anal");
//    analogWrite(motorSpeedPin, defaultSpeed);
//    serialLog.message("analogWrite DONE", "Anal");
//    sprintTimeToSlowDown = millis() + sprintTime;
}

void GateMotor::stopGate() {
    serialLog.message("Stop Gate", "Motor");
    currentCommand = 's';
    digitalWrite(motorDirectionPin1, false);
    digitalWrite(motorDirectionPin2, true);

    // Lower the motor speed to 0
//    serialLog.message("analogWrite", "Anal");
//    analogWrite(motorSpeedPin, 0);
//    serialLog.message("analogWrite DONE", "Anal");
    stopTill = millis() + 5000;
}

void GateMotor::closeGate() {
    serialLog.message("Close Gate", "Motor");
    currentCommand = 'c';
    digitalWrite(motorDirectionPin1, false);
    digitalWrite(motorDirectionPin2, false);

//    serialLog.message("analogWrite", "Anal");
//    analogWrite(motorSpeedPin, defaultSpeed);
//    serialLog.message("analogWrite DONE", "Anal");
}

void GateMotor::runCommands() {
    if(currentCommand == 'c') {
        return; // nothing to do, close till open again.
    }

    float currentSensorValue = getCurrentSensorValue();
    int currentMillis = millis();
    serialLog.message("11111", "runCommands");


    if(currentCommand == 'o') {
        // slow open cycle at the end.
//        if (currentMillis >= sprintTimeToSlowDown) {
//            serialLog.message("Time for opening motor to slow down.", "Motor");
//            serialLog.message("analogWrite", "Anal");
//            analogWrite(motorSpeedPin, defaultSpeed);
//            serialLog.message("analogWrite DONE", "Anal");
//            sprintTimeToSlowDown = 0;
//        }

        // the open motor has stopped.
        if(currentSensorValue <= currentThreshold && stopTill == 0) {
            serialLog.message("Gate Motor has stopped.", "Motor");
            stopTill = currentMillis + 10000;
        }
    }

    if(stopTill > 0 && currentMillis >= stopTill) {
        serialLog.message("Stop Time Over.. closing gate.", "Motor");
        currentCommand = 'c';
    }
}

float GateMotor::getCurrentSensorValue() {
    serialLog.message("getCurrentSensorValue Start", "analogRead");
    int totalSensorValue = 0;
    uint8_t readings = 10;

    for (int i = 0; i < readings; i++) {
        totalSensorValue += analogRead(motorSensorPin) - motorCurrentZeroValue;
    }

    uint16_t avgReading = totalSensorValue / readings;
    motorCurrent.addValue(avgReading);
    serialLog.message("getCurrentSensorValue End", "analogRead");

    return motorCurrent.getAverage();
}

//bool GateMotor::isMoving() {
//  return false;
//}
//
//bool GateMotor::isOpen() {
//  return false;
//}
//
//bool GateMotor::isStopped() {
//  return false;
//}
//
//bool GateMotor::isClosed() {
//  return false;
//}

void GateMotor::calibrateCurrentSensor() {
  uint16_t total = 0;
  
  for (int i = 0; i < 10; i++) {
    delay(20);
    total += (analogRead(motorSensorPin));
  }

  motorCurrentZeroValue = total / 10;
  serialLog.message(&"Calibrated Current Sensor Zero: "[motorCurrentZeroValue], "Motor");
  motorCurrent.fillValue(0, 50);
}
