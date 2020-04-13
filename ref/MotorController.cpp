#include "MotorController.h"
#include "RunningAverage.h"
#include "analogWrite.h"

MotorController::MotorController(
  uint8_t m1E, uint8_t m1A, uint8_t m1B, uint8_t m1C, 
  uint8_t m2E, uint8_t m2A, uint8_t m2B, uint8_t m2C,
  bool debug
  ) : motor1Sensor(25), motor2Sensor(25) {

  this->enableGate();
  
  this->gateMoving = false;
  this->state = 'e';
  this->debugMode = debug;

  this->motor1Enable = m1E;
  this->motor1PinA   = m1A;
  this->motor1PinB   = m1B;
  this->motor1Amps   = m1C;
  pinMode(m1E, OUTPUT);
  pinMode(m1A, OUTPUT);
  pinMode(m1B, OUTPUT);
  pinMode(m1C, INPUT);

  this->motor2Enable = m2E;
  this->motor2PinA   = m2A;
  this->motor2PinB   = m2B;
  this->motor2Amps   = m2C;
  pinMode(m2E, OUTPUT);
  pinMode(m2A, OUTPUT);
  pinMode(m2B, OUTPUT);
  pinMode(m2C, INPUT);

  analogWrite(m1E, 0);
  analogWrite(m2E, 0);

  this->calibrateCurrentSensors();
  this->setMotorsToClose();
  this->moveMotorsTillCurrentDrop();
  this->setMotorsToOff();
  
  this->state = 'c';
}


// ACTION METHODS

void MotorController::triggerOpenCycle(int openPause) { // default 30000, aka 30 secs
  Serial.println("Opening Gate");
  this->openGate();
  Serial.println("Pausing to let car though");
  delay(openPause);
  Serial.println("Closing Gate");
  this->closeGate();
}

void MotorController::openGate() {
  if(!this->isEnabled()) {
    return; 
  }

  if(!this->isClosed()) {
    // this is bad, do something about it
  }

  this->setMotorsToOpen();
  this->waitPIDLoop(255);
  this->setMotorsToOff();

  this->state = 'o';
}

void MotorController::closeGate() {
  if(!this->isEnabled()) {
    return; 
  }

  if(!this->isOpen()) {
    // this is bad, do something about it
  }

  this->setMotorsToClose();
  this->waitPIDLoop(200);
  this->setMotorsToOff();

  this->state = 'c';
}

void MotorController::setMotorsToOpen() {  
  digitalWrite(this->motor1PinA, true);
  digitalWrite(this->motor1PinB, false);

  digitalWrite(this->motor2PinA, true);
  digitalWrite(this->motor2PinB, false);
}

void MotorController::setMotorsToClose() {
  digitalWrite(this->motor1PinA, false);
  digitalWrite(this->motor1PinB, true);

  digitalWrite(this->motor2PinA, false);
  digitalWrite(this->motor2PinB, true);
}

void MotorController::setMotorsToOff() {
  digitalWrite(this->motor1PinA, false);
  digitalWrite(this->motor1PinB, false);

  digitalWrite(this->motor2PinA, false);
  digitalWrite(this->motor2PinB, false);
}

void MotorController::disableGate() {
  this->enabled = false;
}

void MotorController::enableGate() {
  this->enabled = true;
}

void MotorController::moveMotorsTillCurrentDrop(int motorSpeed) {
  analogWrite(this->motor1Enable, motorSpeed);
  analogWrite(this->motor2Enable, motorSpeed);
  this->gateMoving = true;

  delay(1000); // give the motors time to start using current

  float combinedCurrent = 1000;

  while(combinedCurrent > 50) {
    combinedCurrent = this->getCombinedCurrent();
  }

  analogWrite(this->motor1Enable, 0);
  analogWrite(this->motor2Enable, 0);
  this->gateMoving = false;
}

void MotorController::waitPIDLoop(int motorSpeed) {
  analogWrite(this->motor1Enable, motorSpeed);
  analogWrite(this->motor2Enable, motorSpeed);
  this->gateMoving = true;

  delay(200); // give the motors time to start using current

  unsigned long futureTime = millis();
  futureTime += (16*1000);

  while(futureTime > millis()) {
    this->getCombinedCurrent();
  }
  
  this->moveMotorsTillCurrentDrop(200);
}

void MotorController::calibrateCurrentSensors() { 
  uint16_t acc1 = 0;
  uint16_t acc2 = 0;
  
  for (int i = 0; i < 10; i++) {
    delay(20);
    acc1 += abs(analogRead(this->motor1Amps));
    acc2 += abs(analogRead(this->motor2Amps));
  }

  this->motorSensor1Zero = acc1 / 10;
  this->motorSensor2Zero = acc2 / 10;

  this->motor1Sensor.fillValue(0, 50);
  this->motor2Sensor.fillValue(0, 50);
}

float MotorController::getCombinedCurrent() {
  uint16_t acc1 = 0;
  uint16_t acc2 = 0;
  
  for (int i = 0; i < 10; i++) {
    acc1 += abs(analogRead(this->motor1Amps) - this->motorSensor1Zero);
    acc2 += abs(analogRead(this->motor2Amps) - this->motorSensor2Zero);
  }

  acc1 = acc1 / 10;
  this->motor1Sensor.addValue(acc1);
  
  acc2 = acc2 / 10;
  this->motor2Sensor.addValue(acc2);

  float avg1 = this->motor1Sensor.getAverage();
  float avg2 = this->motor2Sensor.getAverage();
  float combined = avg1 + avg2;

  if(this->debugMode) {
    Serial.print(String("Motor1Avg:") + avg1 + " ");
    Serial.print(String("Motor2Avg:") + avg2 + " ");
    Serial.println(String("Combined:") + combined);

//    Serial.print(String("In1:") + acc1 + " ");
//    Serial.print(String("In2:") + acc2 + " ");
//
//    Serial.print(String("Thres1:") + (avg1 * 1.50) + " ");
//    Serial.print(String("Thres2:") + (avg2 * 1.50) + " ");
  }

//  if(acc1 > (avg1 * 1.50) || acc2 > (avg2 * 1.50)) {
//    // motor is out of bounds
//    if(this->isOpen()) {
//      this->openGate();
//      delay(10000);
//      this->closeGate();
//    }
//    if(this->isClosed()) {
//      this->closeGate();
//    }
//
//    this->state = 'e';
//    return 0;
//  }
  
  return combined;
}


// STATUS METHODS

bool MotorController::isOpen() {
  return this->state == 'o';
}

bool MotorController::isClosed() {
  return this->state == 'c';
}

bool MotorController::isUnknown() {
  return this->state == 'u';
}

bool MotorController::isError() {
  return this->state == 'e';
}

bool MotorController::isGateMoving() {
  return this->gateMoving;
}

bool MotorController::isEnabled() {
  return this->enabled;
}
