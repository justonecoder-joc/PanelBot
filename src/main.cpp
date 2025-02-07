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

float delta_time = 500e-3;
PID_Controller pid_mob1(0.1f, 0.001f, 0.001f, 0.0f, 1.0f);
PID_Controller pid_mob2(0.1f, 0.001f, 0.001f, 0.0f, 1.0f);

void setup()
{
  SerialCom.begin(9600);
}

void loop()
{
  
  // limitSwitch.sense();
  // proximitySensor.sense();
  float mob1_speed = pid_mob1.calculate(0.1, encoder.velocity, delta_time);
  float mob2_speed = pid_mob2.calculate(0.1, encoder.velocity, delta_time);
  motor1.set_direction(Forward); // Forward == Left
  motor1.set_speed(mob1_speed);

  motor2.set_direction(Backward); // Backward == Right
  motor2.set_speed(mob2_speed);

  SerialCom.print("Ticks: ");
  SerialCom.println(encoder.ticks);  
  
  SerialCom.print("RPM: ");
  SerialCom.println(encoder.rpm);

  SerialCom.print("Velocity: ");
  SerialCom.println(encoder.velocity);

  // SerialCom.print("Limit Switch State ");
  // SerialCom.println(limitSwitch.state);  
  
  // SerialCom.print("Proximity Sensor State ");
  // SerialCom.println(proximitySensor.state);  

  delay(500);
}
