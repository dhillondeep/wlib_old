/**!
 * @author Deep Dhillon
 * @date October 12, 2017
 * @file blink_led.ino
 *
 * @section Description
 * wlib LED blink demonstration. It uses OOP for IO management and adds some new
 * method to make life easier when dealing with arduino pins. It also provides
 * operator overloading to make reading and writing easier.
 *
 * @section Circuit
 * Uses built-in LED (D13)
 */

#include <Wlib.h>
#include <core/pins/DigitalPins.h>

// create a digital pin object for pin 13
DigitalPins<BOARD::D13> ledPin;

void setup(){
    Serial.begin(9600);

    // make ledPin output pin
    ledPin.output();

    bool currValue;

    ledPin >> currValue;

    Serial.println("Current LED Value (operator overloading): " + currValue);
    Serial.println("Current LED Value (simple): " + ledPin.read());
}

void loop(){
    ledPin.toggle();    // toggles the pin on every call
    delay(1000);

    // operator overloading
    ledPin << HIGH;
    delay(1000);
    ledPin << LOW;
    delay(1000);

    // without operator overloading
    ledPin.high();
    delay(1000);
    ledPin.low();
    delay(1000);

    //write any value (anything more than 0 is HIGH and 0 is LOW)
    ledPin.write(120);

    // Pulse width 1..10 us, not interrupted
    for (uint16_t width = 1; width < 11; width++)
        ledPin.writePulse(width);

    // Delay 10 us but observe with logic analyzer variation 10,15 us
    // as timer interrupts will occur here
    delayMicroseconds(10);
}
