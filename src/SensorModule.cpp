#include "SensorModule.h"
#include "Log.h"

SensorModule::SensorModule():
  houseCenter(),
  roadRight(),
  roadLeft()
{
  ads.begin();
}

void SensorModule::readSensors() {
  lightSensor1Value = ads.readADC_SingleEnded(0);
  lightSensor2Value = ads.readADC_SingleEnded(2);
  lightSensor3Value = ads.readADC_SingleEnded(3);
  buttonValue       = ads.readADC_SingleEnded(1);

  serialLog.plot("SM", "Light1", lightSensor1Value);
  serialLog.plot("SM", "Light2", lightSensor2Value);
  serialLog.plot("SM", "Light3", lightSensor3Value);
  serialLog.plot("SM", "Button", buttonValue, true);
}

bool SensorModule::buttonPressed() {
  if(buttonValue > 1200) {
    serialLog.message("Button Pressed!");

    return true;
  }

  return false;
}

bool SensorModule::lightFlashed() {
  if(houseCenter.isTriggered(lightSensor1Value)) {
    serialLog.message("Light1 Triggered.");

    return true;
  }

  if(roadRight.isTriggered(lightSensor2Value)) {
    serialLog.message("Light2 Triggered.");

    return true;
  }

  if(roadLeft.isTriggered(lightSensor3Value)) {
    serialLog.message("Light3 Triggered.");

    return true;
  }
  
  return false;
}
