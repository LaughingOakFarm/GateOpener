#ifndef GATECONTROLLER_H
#define GATECONTROLLER_H

#include "GateMotor.h"

class GateMotor;

class GateController {
  private:
    char currentCommand = 'u'; // unknown, open, close, stop, none
    GateMotor leftMotor;
    GateMotor rightMotor;
   
  public:
    GateController();
    
    void initLeftMotor(uint8_t speedPin, uint8_t direction1Pin, uint8_t direction2Pin, uint8_t sensorPin);
    void initRightMotor(uint8_t speedPin, uint8_t direction1Pin, uint8_t direction2Pin, uint8_t sensorPin);
    void openGate();
    void stopGate();
    void closeGate();
//    void triggered();

//    bool isMoving();
//    bool isOpen();
//    bool isStopped();
//    bool isClosed();
//    void runCommands();
//    void buttonPressed();

};

#endif
