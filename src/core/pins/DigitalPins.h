#ifndef WLIB_DIGITALPINS_H
#define WLIB_DIGITALPINS_H

#include <Wlib.h>
#include <GPIO.h>

template<BOARD::pin_t PIN>
class DigitalPins {
    GPIO<PIN> gpio;
public:
    inline void input(){ gpio.input(); }

    inline void output(){ gpio.output(); }

    inline void openDrain() { gpio.open_drain(); }

    inline void pullUp() { gpio.pullup(); }

    inline void high(){ gpio.high(); }

    inline void low(){ gpio.low(); }

    inline void toggle(){ gpio.toggle(); }

    inline void write(uint8_t val){ gpio.write(val); }

    inline bool read(){ return gpio.read(); }

    inline void operator<<(uint8_t value){ write(value); }

    inline void operator>>(bool &var){ var = read(); }

    inline void writePulse(uint8_t width) { gpio.pulse(width); }

    inline int readPulse(uint8_t width) { return gpio.pulse(); }
};


#endif //WLIB_DIGITALPINS_H
