#include "LightSensor.h"
#include "Log.h"

LightSensor::LightSensor() : avg(250) {}

bool LightSensor::isTriggered(int rawLightInput) {

  double currentMicros = micros();
  bool trigger = false;

  // Should the code check yet?
  if (currentMicros > (lastLoopMicro + interval)){
    lastLoopMicro = currentMicros;
    
    avg.addValue(rawLightInput);
    float currentAvg = avg.getAverage();

    // falling edge detected
    float fallingEdgeThres = currentAvg * 0.75;
    if(!detectingFlash && rawLightInput < fallingEdgeThres) {
      detectingFlash = true;

      if(lightFlashNum == 0) {
        flashTimer = hz * 3; // we have 3 seconds
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
    float risingEdgeThres = currentAvg * 0.9;
    if(rawLightInput > risingEdgeThres) {
      detectingFlash = false;
    }

    serialLog.plot("LS", "LightInput", rawLightInput);
    serialLog.plot("LS", "Avg", currentAvg);
    serialLog.plot("LS", "FallingEdge", fallingEdgeThres);
    serialLog.plot("LS", "RisingEdge", risingEdgeThres);
    serialLog.plot("LS", "DetectingFlag", (detectingFlash * 100));
    serialLog.plot("LS", "FlashCount", (lightFlashNum * 100));
    serialLog.plot("LS", "Trigger", (trigger * 1000));
    serialLog.plot("LS", "Timer", flashTimer, true);

    if(flashTimer) {
      flashTimer--;
    }

    if(flashTimer == 0) {
      lightFlashNum = 0;
    }
  }

  return trigger;
}
