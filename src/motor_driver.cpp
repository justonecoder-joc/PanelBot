#include"motor_driver.hpp"


MotorDriver::MotorDriver(uint8_t pinL, uint8_t pinR)
{
    pinL_i = pinL;
    pinR_i = pinR;

    pinMode(pinL_i, OUTPUT);
    pinMode(pinR_i, OUTPUT);

    speed_f = 0.0f;
    direction_i = Forward;

    this->set_speed(speed_f); // Motor is turned-off at the start.
}

void MotorDriver::set_speed(float speed)
{
    speed_f = speed;
    uint8_t speed_pwm = speed * 255;

    switch (direction_i)
    {
    case Forward:
        analogWrite(pinL_i, speed_pwm);
        analogWrite(pinR_i, 0);
        break;
    case Backward:
        analogWrite(pinL_i, 0);
        analogWrite(pinR_i, speed_pwm);
        break;
    default:
        analogWrite(pinL_i, 0);
        analogWrite(pinR_i, 0);
        break;
    }
}

void MotorDriver::set_direction(Direction direction)
{
    direction_i = direction;
    set_speed(speed_f);
}
