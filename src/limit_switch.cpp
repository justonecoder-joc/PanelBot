#include "limit_switch.hpp"

LimitSwitch::LimitSwitch(uint8_t pin)
{
    pin_i = pin;
    pinMode(pin_i, INPUT_PULLUP);
}

void LimitSwitch::sense()
{
    state = digitalRead(pin_i);
}