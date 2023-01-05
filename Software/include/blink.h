#ifndef LED_H_
#define LED_H_

#include <Arduino.h>

class led {
    
    private:
        uint8_t _pin;
        boolean _state = LOW;

    public:
        led(uint8_t pin);       //Constructor

        void on(void);
        void off(void);
        void changeState();
        void flipState();
};

#endif