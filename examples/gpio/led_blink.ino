#include <Arduino.h>
#include <gpio/GPIO.h>

GPIO<BOARD::D13> ledPin;

void setup(){
    ledPin.output();
}

void loop(){
    ledPin = HIGH;
    delay(1000);

    ledPin = LOW;
    delay(1000);
}
