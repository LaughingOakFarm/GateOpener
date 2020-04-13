#include "Log.h"
#include "GateController.h"
#include "SensorModule.h"

SensorModule sensorModule;
GateController gateController;
Log serialLog;

void setup() {
  serialLog.init();
  serialLog.setPlotGroup("none"); // none, SM, LS
  gateController.initLeftMotor(
    27, // Motor 1 Enable
    14, // Motor 1 A Pin
    32, // Motor 1 B Pin
    34  // Motor 1 Current 
  );
  gateController.initRightMotor(
    26, // Motor 2 Enable
    25, // Motor 2 A Pin
    33, // Motor 2 B Pin
    35  // Motor 2 Current  
  );
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