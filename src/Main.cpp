#include "Log.h"
#include "GateController.h"
#include "SensorModule.h"

SensorModule sensorModule;
GateController gateController;
Log serialLog;

void setup() {
  serialLog.init();
  serialLog.setPlotGroup("none"); // none, SM, LS
  gateController.initLeftMotor(27,14,32,34);
  gateController.initRightMotor(26,25,33,35);
}

void loop() {
  sensorModule.readSensors();
  
  if (sensorModule.lightFlashed()) {
    gateController.openGate();
  }

  if (sensorModule.buttonPressed()) {
    gateController.openGate();
  }
}