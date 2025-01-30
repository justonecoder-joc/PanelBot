#include "PID.hpp"

// initializing PID gains and output limits
PID_Controller::PID_Controller(float p, float i, float d, float minimum_output, float maximum_output)
{
    Kp = p;
    Ki = i;
    Kd = d;

    outputMax = maximum_output;
    outputMin = minimum_output;

    previousError = 0;
    integral = 0;
}

// Calculating PID output
float PID_Controller::calculate(float setpoint, float current_value, float deltaTime)
{
    // calculating the error
    float error = setpoint - current_value;

    // calculating integral term i.e. the error it is accumulating over time
    integral += error * deltaTime;

    // calculating the derivative term i.e. the rate of change of error
    float derivative = (error - previousError) / deltaTime;

    // PID output calculation
    float output = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // P(Proportional): Reacts to the current error (how far you are from the target).
    // I(Integral) : Remembers the past errors(to fix long - term drift).
    // D(Derivative) : Predicts the future(to stop overshooting).

    // Let us constraint the output

    if (output > outputMax)
    {
        output = outputMax;
    }
    else if (output < outputMin)
    {
        output = outputMin;
    }

    previousError = error;

    return output;
}

// resetting the PID controller state

void PID_Controller::reset()
{
    previousError = 0;
    integral = 0;
}