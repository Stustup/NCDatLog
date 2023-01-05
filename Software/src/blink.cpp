#include <Arduino.h>
#include <debug.h>
#include <blink.h>

led::led(uint8_t pin) {
    _pin = pin;

    pinMode(_pin, OUTPUT);
    _state = LOW;
    changeState();
}

void led::on(void) {

    #ifdef debug 
        if(!_state) Serial.println("LED on");
    #endif
    
    _state = HIGH;
    changeState();
}

void led::off(void) {

    #ifdef debug 
        if(_state) Serial.println("LED off");
    #endif

    _state = LOW;
    changeState();
}

void led::changeState() {
    digitalWrite(_pin, _state);
}

void led::flipState() {
    digitalWrite(_pin, _state);
    _state = !_state;
}