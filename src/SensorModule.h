#ifndef SENSORMODULE_H
#define SENSORMODULE_H

#include "LightSensor.h"
#include "../.pio/libdeps/esp32doit-devkit-v1/Adafruit ADS1X15_ID342/Adafruit_ADS1015.h"

class Adafruit_ADS1015;

class SensorModule {
  private:
    bool buttonPressedDown = false;
    Adafruit_ADS1015 ads;
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
