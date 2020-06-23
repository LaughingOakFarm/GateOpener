#ifndef SENSORMODULE_H
#define SENSORMODULE_H

#include "LightSensor.h"

class SensorModule {
  private:
    double buttonCoolDownTill = 0;
    const int buttonGPIO = 3;
 
    LightSensor sensorA0;
    LightSensor sensorA1;
    LightSensor sensorA2;
    LightSensor sensorA3;
    LightSensor sensorA4;
    LightSensor sensorA5;

    int lightSensorA0Value;
    int lightSensorA1Value;
    int lightSensorA2Value;
    int lightSensorA3Value;
    int lightSensorA4Value;
    int lightSensorA5Value;
    int buttonValue;

    int buttonCount = 0;

  public:
    SensorModule();

    void readSensors();
    bool lightFlashed();
    bool buttonPressed();
};

#endif


//    int rawReadings [100];
