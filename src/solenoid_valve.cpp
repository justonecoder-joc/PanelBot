#include "solenoid_valve.hpp"

SolenoidValve::SolenoidValve(uint8_t pin)
{
    pin_i = pin;
    state = OFF;

    pinMode(pin_i, OUTPUT);
    digitalWrite(pin_i, state);
}

void SolenoidValve::turnOn()
{
    state = ON;
    digitalWrite(pin_i, state);
}

void SolenoidValve::turnOff()
{
    state = OFF;
    digitalWrite(pin_i, state);
}

ValveState SolenoidValve::getState()
{
    return state;
}