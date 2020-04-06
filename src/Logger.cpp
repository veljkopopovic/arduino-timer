#include "Logger.h"
#include <Arduino.h>

void Logger::log(const char* format, ...) {
  va_list arguments;
  va_start (arguments, format);

  char buf[128];
  vsprintf(buf, format, arguments);
  va_end(arguments);

  Serial.println(buf);
}