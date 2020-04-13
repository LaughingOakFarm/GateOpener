#include "Log.h"

Log::Log() {}

void Log::init() {
  Serial.begin(115200);
  plotGroup = "none";
  serialLog.message("Serial Log Init");
}

void Log::message(String message) {
  if(plotGroup == "none") {
    Serial.println(String("Log: " + message)); 
  }
}

void Log::setPlotGroup(String groupName) {
  plotGroup = groupName;
  serialLog.message("Plot Group set to: "+plotGroup);
}

void Log::plot(String groupName, String varName, int varValue, bool newLine) {
  if(plotGroup == groupName) {
    if(newLine) {
      Serial.println(varName+":"+varValue);
    } else {
      Serial.print(varName+":"+varValue+" ");
    }
  }
}
