#ifndef LOG_H
#define LOG_H

#include "Arduino.h"

class Log {
  private:
   
  public:
    Log();

    void init();
    void message(String message, String prefix = "Log");
    void setPlotGroup(String groupName = "none");
    void plot(String groupName, String varName, int varValue, bool newLine = false);

    String plotGroup;
};

extern Log serialLog;

#endif
