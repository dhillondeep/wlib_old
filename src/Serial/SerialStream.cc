#include <Arduino.h>
#include "SerialStream.h"

extern wlp::SerialStream serialstream;

void wlp::SerialStream::start(unsigned long baud) {
	Serial.begin(baud);
}

