#include "Arduino.h"
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
    gateController.initLeftMotor(7,8,9,6);
    gateController.initRightMotor(12,11,10,5);

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
