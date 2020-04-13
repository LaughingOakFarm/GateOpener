#ifndef GATECONTROLLER_H
#define GATECONTROLLER_H

#include "GateMotor.h"

class GateMotor;

class GateController {
  private:
    char currentCommand = 'n'; // none, open, close, stop
    GateMotor leftMotor;
    GateMotor rightMotor;
   
  public:
    GateController();
    
    void initLeftMotor(uint8_t speedPin, uint8_t direction1Pin, uint8_t direction2Pin, uint8_t sensorPin);
    void initRightMotor(uint8_t speedPin, uint8_t direction1Pin, uint8_t direction2Pin, uint8_t sensorPin);
    void openGate(int openPause = 30000);
    void stopGate();
    void closeGate();

    bool isMoving();
    bool isOpen();
    bool isStopped();
    bool isClosed();
};

#endif
