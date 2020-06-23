#include "SensorModule.h"
#include "Log.h"

SensorModule::SensorModule() :
        sensorA0("A0"),
        sensorA1("A1"),
        sensorA2("A2"),
        sensorA3("A3"),
        sensorA4("A4"),
        sensorA5("A5") {
    pinMode(buttonGPIO, INPUT_PULLUP);
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
}

void SensorModule::readSensors() {
    lightSensorA0Value = analogRead(A0);
    lightSensorA1Value = analogRead(A1);
    lightSensorA2Value = analogRead(A2);
    lightSensorA3Value = analogRead(A3);
    lightSensorA4Value = analogRead(A4);
    lightSensorA5Value = analogRead(A5);
    buttonValue = digitalRead(buttonGPIO);

    serialLog.plot("SM", "A0", lightSensorA0Value);
    serialLog.plot("SM", "A1", lightSensorA1Value);
    serialLog.plot("SM", "A2", lightSensorA2Value);
    serialLog.plot("SM", "A3", lightSensorA3Value);
    serialLog.plot("SM", "A4", lightSensorA4Value);
    serialLog.plot("SM", "A5", lightSensorA5Value);
    serialLog.plot("SM", "Button", buttonValue, true);

    serialLog.plot("Button", "Button", buttonValue, true);
    serialLog.plot("Button", "Count", buttonCount, true);
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
        if(buttonCount == 3) {
          buttonCoolDownTill = millis() + 1000;
          serialLog.message(String(buttonValue));
          serialLog.message("Button Pressed!", "SM");

          return true;
        }

        buttonCount++;
    } else {
      buttonCount = 0;
    }

    return false;
}

bool SensorModule::lightFlashed() {
    if (sensorA0.isTriggered(lightSensorA0Value)) {
        serialLog.message("A0 Triggered.", "SM");

        return true;
    }

    if (sensorA1.isTriggered(lightSensorA1Value)) {
        serialLog.message("A1 Triggered.", "SM");

        return true;
    }
    
    if (sensorA2.isTriggered(lightSensorA2Value)) {
        serialLog.message("A2 Triggered.", "SM");

        return true;
    }

    if (sensorA3.isTriggered(lightSensorA3Value)) {
        serialLog.message("A3 Triggered.", "SM");

        return true;
    }

    if (sensorA4.isTriggered(lightSensorA4Value)) {
        serialLog.message("A4 Triggered.", "SM");

        return true;
    }

    if (sensorA5.isTriggered(lightSensorA5Value)) {
        serialLog.message("A5 Triggered.", "SM");

        return true;
    }

    return false;
}
