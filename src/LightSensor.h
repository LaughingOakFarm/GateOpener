#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "Arduino.h"

class LightSensor {
  private:
    int hz = 50;
    int interval = 1000000 / hz;
    int lastLoopMicro = 0;
        
    bool detectingFlash = false;
    int lightFlashNum = 0;
    int flashTimer = 0;
    int lightFlashThresh = 4;
    String sensorName = "";
    float currentAvg = 1;
    
  public:
    LightSensor(String name = "");
    bool isTriggered(int rawLightInput);
};

#endif
