#ifndef SENSORMODULE_H
#define SENSORMODULE_H

#include "LightSensor.h"

class SensorModule {
  private:
    double buttonCoolDownTill = 0;
    const int buttonGPIO = 3;
    LightSensor houseCenter;
    LightSensor roadRight;
    LightSensor roadLeft;
    
    int lightSensor1Value;
    int lightSensor2Value;
    int lightSensor3Value;
    int buttonValue;

  public:
    SensorModule();

    void readSensors();
    bool lightFlashed();
    bool buttonPressed();
};

#endif


//    int rawReadings [100];
