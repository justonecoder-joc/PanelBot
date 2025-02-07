#include <Arduino.h>
#pragma once

class PID_Controller
{
private:
    // PID Gains
    float Kp;
    float Kd;
    float Ki;

    float previousError; // this will store the previous error for the derivative calculation
    float integral;      // accumulates tthe error over time for the integral term

    // limits for PID controller
    float outputMin;
    float outputMax;

public:
    PID_Controller(float p, float i, float d, float minimum_output, float maximum_output);

    // to calculate the PID output
    float calculate(float setpoint, float current_value, float deltaTime);
    
    // setpoint = RPM of the robot i.e. the speed at which you want the robot to move
    // current_value = the current value that is being measured through the encoder
    // deltaTime = calculates how fast things are changing. Necessary because the integral term accumulates error over time. Without this, the accumulated integral can grow too fast or too slow, making the system unstable

    void reset(); // Method to reset the integral and previous error (useful during reinitialization)
};