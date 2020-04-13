#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "RunningAverage.h"

class RunningAverage;

class MotorController {
  private:
    bool enabled;
    bool gateMoving;
    char state = 'e'; // 'o', 'c', 'e', 'u'
    int threshold = 140;
    bool debugMode = false;

    uint8_t motor1Enable;
    uint8_t motor1PinA;
    uint8_t motor1PinB;
    uint8_t motor1Amps;
    uint16_t motorSensor1Zero;
    RunningAverage motor1Sensor;

    uint8_t motor2Enable;
    uint8_t motor2PinA;
    uint8_t motor2PinB;
    uint8_t motor2Amps;
    uint16_t motorSensor2Zero;
    RunningAverage motor2Sensor;

    void setMotorsToClose();
    void setMotorsToOpen();
    void moveMotorsTillCurrentDrop(int motorSpeed = 255);
    void waitPIDLoop(int motorSpeed = 255);
    void calibrateCurrentSensors();
    float getCombinedCurrent();
   
  public:
    MotorController(uint8_t m1E, uint8_t m1A, uint8_t m1B, uint8_t m1C, uint8_t m2E, uint8_t m2A, uint8_t m2B, uint8_t m2C, bool debug = false);
    
    void openGate();
    void closeGate();
    void triggerOpenCycle(int openPause = 30000);
    void disableGate();
    void enableGate();
    void setMotorsToOff();
    void clearError();
    
    bool isOpen();
    bool isClosed();
    bool isUnknown();
    bool isError();
    bool isGateMoving();
    bool isEnabled();
};

#endif
