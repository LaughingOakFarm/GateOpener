#include "Log.h"
#include "GateController.h"
#include "SensorModule.h"

SensorModule sensorModule;
GateController gateController;
Log serialLog;

void setup() {
    delay(1000);
    serialLog.init();
    serialLog.setPlotGroup("none"); // none, SM, LS
    gateController.initLeftMotor(27,14,32,34);
    gateController.initRightMotor(26,25,33,35);

    delay(1000);
    gateController.closeGate();

    serialLog.message("----- SETUP DONE! -----", "Main");
}

void loop() {
    sensorModule.readSensors();

    if(sensorModule.lightFlashed()) {
        gateController.openGate();
    } else if (sensorModule.buttonPressed()) {
        gateController.openGate();
    }
}