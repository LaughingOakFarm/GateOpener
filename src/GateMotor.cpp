#include "GateMotor.h"
#include "Log.h"
#include "analogWrite.h"

GateMotor::GateMotor() : motorCurrent(50) {}

GateMotor::GateMotor(
        uint8_t speedPin,
        uint8_t directionPin1,
        uint8_t directionPin2,
        uint8_t sensorPin) : motorCurrent(50) {

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

void GateMotor::openGate(bool block, int speed) {
    serialLog.message("Open Gate", "Motor");
    currentCommand = 'o';

    digitalWrite(motorDirectionPin1, true);
    digitalWrite(motorDirectionPin2, false);

    analogWrite(motorSpeedPin, speed);

    if(block) {
        delay(1000); // get the motors going..
        blockTillMotorStops();
    }
}

void GateMotor::stopGate() {
    serialLog.message("Stop Gate", "Motor");
    currentCommand = 's';

    digitalWrite(motorDirectionPin2, false);
    digitalWrite(motorDirectionPin1, false);
    analogWrite(motorSpeedPin, 0);
}

void GateMotor::closeGate(bool block) {
    serialLog.message("Close Gate", "Motor");
    currentCommand = 'c';

    digitalWrite(motorDirectionPin1, false);
    digitalWrite(motorDirectionPin2, true);

    analogWrite(motorSpeedPin, sprintSpeed);

    if(block) {
        delay(1000); // get the motors going..
        blockTillMotorStops();
    }
}

//void GateMotor::runCommands() {
//    if(currentCommand == 'c') {
//        return; // nothing to do, close till open again.
//    }
//
//    float currentSensorValue = getCurrentSensorValue();
//    int currentMillis = millis();
//    serialLog.message("11111", "runCommands");
//
//
//    if(currentCommand == 'o') {
//        // slow open cycle at the end.
//        if (currentMillis >= sprintTimeToSlowDown) {
//            serialLog.message("Time for opening motor to slow down.", "Motor");
//            serialLog.message("analogWrite", "Anal");
//            analogWrite(motorSpeedPin, defaultSpeed);
//            serialLog.message("analogWrite DONE", "Anal");
//            sprintTimeToSlowDown = 0;
//        }
//
//        // the open motor has stopped.
//        if(currentSensorValue <= currentThreshold && stopTill == 0) {
//            serialLog.message("Gate Motor has stopped.", "Motor");
//            stopTill = currentMillis + 10000;
//        }
//    }
//
//    if(stopTill > 0 && currentMillis >= stopTill) {
//        serialLog.message("Stop Time Over.. closing gate.", "Motor");
//        currentCommand = 'c';
//    }
//}

void GateMotor::blockTillMotorStops() {
    float currentSensorValue = 1000;

    while(currentSensorValue >= currentThreshold) {
        currentSensorValue = getCurrentSensorValue();
        delay(100);
    }
}

float GateMotor::getCurrentSensorValue() {
    int totalSensorValue = 0;
    uint8_t readings = 10;

    for (int i = 0; i < readings; i++) {
        totalSensorValue += analogRead(motorSensorPin) - motorCurrentZeroValue;
    }

//    uint16_t avgReading = totalSensorValue / readings;
//    serialLog.message(String(avgReading), "avgReading");
//    motorCurrent.addValue(avgReading);

//    serialLog.message(String(motorCurrent.getCount()), "Count");

//    serialLog.message(String(motorCurrent.getAverage()), "getAverage");
    return totalSensorValue / readings;
}

void GateMotor::calibrateCurrentSensor() {
  int total = 0;
  
  for (int i = 0; i < 10; i++) {
    delay(20);
    total += (analogRead(motorSensorPin));
  }

  motorCurrentZeroValue = total / 10;
  serialLog.message("Calibrated Current Sensor Zero: " + String(motorCurrentZeroValue), "Motor");
//  motorCurrent.fillValue(0, 50);
}
