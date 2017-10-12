#include <Arduino.h>
#include <scheduler/Scheduler.h>

void loop1();

void setup(){
    Serial.begin(9600);
    
    Scheduler.startLoop(loop1);
    ledPin.output();
}

void loop1(){
    Serial.println("Loop 1");
    delay(40);
}

void loop(){
    Serial.println("Loop 2");
    delay(40);
}
//
// Created by ds3dhill on 2017-10-11.
//

