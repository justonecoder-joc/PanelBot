#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include "proximity_sensor.hpp"
#include "limit_switch.hpp"
#include "motor_driver.hpp"
#include "encoder.hpp"

HardwareSerial SerialCom(PA10, PA9);

// LimitSwitch limitSwitch(PB4);
// ProximitySensor proximitySensor(PB5);
// MotorDriver motor1(PB6, PB7); //Left Pin, Right Pin
// MotorDriver motor2(PB8, PB9); //Left Pin, Right Pin

Encoder encoder(PB6, PB7, 2, TIM2); // A 2 Hz RPMS calculation interval produced the best results.

void setup()
{
  SerialCom.begin(9600);
}

void loop()
{
  // limitSwitch.sense();
  // proximitySensor.sense();

  // motor1.set_direction(Forward); // Forward == Left
  // motor1.set_speed(0.1);

  // motor2.set_direction(Backward); // Backward == Right
  // motor2.set_speed(0.7);

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
