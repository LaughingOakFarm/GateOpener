#include "LightSensor.h"
#include "Log.h"

LightSensor::LightSensor(String name) {
    sensorName = name;
}

bool LightSensor::isTriggered(int rawLightInput) {

  double currentMicros = micros();
  bool trigger = false;

  // Should the code check yet?
  if (currentMicros > (lastLoopMicro + interval)){
    lastLoopMicro = currentMicros;
    
    currentAvg = ((currentAvg*9)+rawLightInput)/10;

    // falling edge detected
    float fallingEdgeThres = currentAvg * 0.85;
    if(!detectingFlash && rawLightInput < fallingEdgeThres) {
      detectingFlash = true;

      if(lightFlashNum == 0) {
        flashTimer = hz * 4; // we have 4 seconds
      }
      
      lightFlashNum++;
    }

    if(lightFlashNum >= lightFlashThresh) {
      detectingFlash = false;
      lightFlashNum = 0;
      flashTimer = 0;

      trigger = true;
    }

    // rising edge detected
    float risingEdgeThres = currentAvg * 0.95;
    if(rawLightInput > risingEdgeThres) {
      detectingFlash = false;
    }

    serialLog.plot(sensorName, "LightInput", rawLightInput);
    serialLog.plot(sensorName, "Avg", currentAvg);
    serialLog.plot(sensorName, "FallingEdge", fallingEdgeThres);
    serialLog.plot(sensorName, "RisingEdge", risingEdgeThres);
    serialLog.plot(sensorName, "DetectingFlag", (detectingFlash * 100));
    serialLog.plot(sensorName, "FlashCount", (lightFlashNum * 100));
    serialLog.plot(sensorName, "Trigger", (trigger * 1000));
    serialLog.plot(sensorName, "Timer", flashTimer, true);

    if(flashTimer) {
      flashTimer--;
    }

    if(flashTimer == 0) {
      lightFlashNum = 0;
    }
  }

  return trigger;
}
