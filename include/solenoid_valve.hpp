#pragma one
#include <Arduino.h>
#include "stdint.h"

enum ValveState {ON, OFF}; // Low turns on, High turns off.

class SolenoidValve
{
    public:
        SolenoidValve(uint8_t pin);
        void turnOn();
        void turnOff();
        ValveState getState();
        
        private:
        uint8_t pin_i;
        ValveState state;
};