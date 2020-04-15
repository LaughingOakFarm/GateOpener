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
    gateController.closeGate();

    serialLog.message("----- SETUP DONE! -----", "Main");
}

void loop() {\
    serialLog.message("Start of Loop", "Main");
    sensorModule.readSensors();

    if (sensorModule.lightFlashed()) {
        gateController.openGate();
    }

    if (sensorModule.buttonPressed()) {
        gateController.buttonPressed();
    }

    serialLog.message("Start of runCommands", "Main");
    gateController.runCommands();
    serialLog.message("End of Loop", "Main");
}