#pragma once 
#include <Arduino.h>
#include <stdint.h>

class LimitSwitch
{
    public:
        LimitSwitch(uint8_t pin);
        void sense();

        uint8_t state = 1;

    private:
        uint8_t pin_i;
};