#include "SensorModule.h"
#include "Log.h"

SensorModule::SensorModule() :
        houseCenter("LS1"),
        roadRight("LS2"),
        roadLeft("LS3") {
    pinMode(buttonGPIO, INPUT_PULLUP);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
}

void SensorModule::readSensors() {
    lightSensor1Value = analogRead(A3);
    lightSensor2Value = analogRead(A4);
    lightSensor3Value = analogRead(A5);
    buttonValue = digitalRead(buttonGPIO);

    serialLog.plot("SM", "Light1", lightSensor1Value);
    serialLog.plot("SM", "Light2", lightSensor2Value);
    serialLog.plot("SM", "Light3", lightSensor3Value);
    serialLog.plot("SM", "Button", buttonValue, true);
}

bool SensorModule::buttonPressed() {
    if (millis() < buttonCoolDownTill) { // under button cool down time
        return false;
    }

    if (buttonCoolDownTill > 0) { // cool down time over
        buttonCoolDownTill = 0;
        serialLog.message("Button Cool Down Time is over.", "SM");
    }

    if (buttonValue == 0) { // button pressed down
        buttonCoolDownTill = millis() + 1000;
        serialLog.message(String(buttonValue));
        serialLog.message("Button Pressed!", "SM");

        return true;
    }

    return false;
}

bool SensorModule::lightFlashed() {
    if (houseCenter.isTriggered(lightSensor1Value)) {
        serialLog.message("Light1 Triggered.", "SM");

        return true;
    }

    if (roadRight.isTriggered(lightSensor2Value)) {
        serialLog.message("Light2 Triggered.", "SM");

        return true;
    }

    if (roadLeft.isTriggered(lightSensor3Value)) {
        serialLog.message("Light3 Triggered.", "SM");

        return true;
    }

    return false;
}
