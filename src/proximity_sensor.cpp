#include "proximity_sensor.hpp"

ProximitySensor::ProximitySensor(uint8_t pin)
{
    pin_i = pin;
    pinMode(pin_i, INPUT_PULLUP);
}

void ProximitySensor::sense()
{
    state = digitalRead(pin_i);
}