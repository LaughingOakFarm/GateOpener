#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "RunningAverage.h"

class RunningAverage;

class LightSensor {
  private:
    int hz = 50;
    int interval = 1000000 / hz;
    int lastLoopMicro = 0;
        
    bool detectingFlash = false;
    int lightFlashNum = 0;
    int flashTimer = 0;
    int lightFlashThresh = 3;
    String sensorName = "";
    
  public:
    LightSensor(String name = "");
    RunningAverage avg;
    bool isTriggered(int rawLightInput);
};

#endif
