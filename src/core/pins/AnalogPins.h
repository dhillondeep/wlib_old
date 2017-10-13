#ifndef WLIB_ANALOGPINS_H
#define WLIB_ANALOGPINS_H

#include "../../Wlib.h"
#include "../Board.h"

template<BOARD::pin_t PIN>
class AnalogPins {
    uint8_t pin;
public:
    AnalogPins(){
        pin = static_cast<uint8_t>(PIN);
    }

    inline int read(){
        if (pin < Board::A0) return -1;
        return analogRead(pin);
    }

    inline void write(int val){
        if (pin < Board::A0) return;
        analogWrite(pin, val);
    }
};


#endif //WLIB_ANALOGPINS_H
