#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include "proximity_sensor.hpp"
#include "limit_switch.hpp"
#include "motor_driver.hpp"
#include "encoder.hpp"
#include "PID.hpp"

HardwareSerial SerialCom(PA10, PA9);

// LimitSwitch limitSwitch(PB4);
// ProximitySensor proximitySensor(PB5);
MotorDriver motor1(PA2, PA3); //Left Pin, Right Pin
MotorDriver motor2(PB8, PB9); //Left Pin, Right Pin
Encoder encoder(PB6, PB7, 2, TIM3); // A 2 Hz RPMS calculation interval produced the best results.

float mob1_speed = 0.0f;
float mob2_speed = 0.0f;
float velocity_2 = 0.0f;
uint32_t n = 0; // For averaging velocity.
uint32_t n_print = 0;

float delta_time = 100e-3;
PID_Controller pid_mob1(2.0f, 0.1f, 0.1f, 0.0f, 1.0f);
PID_Controller pid_mob2(2.0f, 0.1f, 0.1f, 0.0f, 1.0f);

uint32_t time_stamp = 0;

void setup()
{
  SerialCom.begin(9600);
  motor1.set_direction(Forward); // Forward == Left
  motor1.set_speed(0.5);
  
  motor2.set_direction(Backward); // Backward == Right
  motor2.set_speed(0.5);
  time_stamp = millis();
}

void loop()
{
  
  // limitSwitch.sense();
  // proximitySensor.sense();
  
  
  // SerialCom.print("Limit Switch State ");
  // SerialCom.println(limitSwitch.state);  
  
  // SerialCom.print("Proximity Sensor State ");
  // SerialCom.println(proximitySensor.state);  
  velocity_2 += encoder.velocity;
  n++;

  if (n_print >= 10)
  {
    SerialCom.print("PID output: ");
    SerialCom.println(mob2_speed);  
    
    SerialCom.print("RPM: ");
    SerialCom.println(encoder.rpm);
  
    SerialCom.print("Average Velocity: ");
    SerialCom.println(velocity_2 / n);
    n_print = 0;
  }

  uint32_t current_time = millis();
  if ((current_time - time_stamp) > 50)
  {
    velocity_2 = velocity_2 / n; // Average velocity.
    mob1_speed = pid_mob1.calculate(0.14, encoder.velocity, delta_time);
    mob2_speed = pid_mob2.calculate(0.14, velocity_2, delta_time);
    // motor1.set_direction(Forward); // Forward == Left
    motor1.set_speed(mob1_speed);
    
    // motor2.set_direction(Backward); // Backward == Right
    motor2.set_speed(mob2_speed);
    
    velocity_2 = 0.0f;
    n = 0;
    n_print++;\
    time_stamp = current_time;
  }

  delay(10);
}
