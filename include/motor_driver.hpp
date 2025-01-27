#pragma once 
#include <Arduino.h>
#include <stdint.h>

enum Direction {Forward = 1, Backward = 2};

class MotorDriver
{
    public:
        MotorDriver(uint8_t pinL, uint8_t pinR);
        void set_speed(float speed);
        void set_direction(Direction direction);

    private:
        float speed_f = 0.0f;
        Direction direction_i = Forward;
        uint8_t pinL_i;
        uint8_t pinR_i;
};