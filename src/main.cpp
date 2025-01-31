#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
// #include "proximity_sensor.hpp"
// #include "limit_switch.hpp"
// #include "motor_driver.hpp"

HardwareSerial SerialCom(PA10, PA9);

uint32_t clk_time = 0;
// LimitSwitch limitSwitch(PB4);
// ProximitySensor proximitySensor(PB5);
// MotorDriver motor1(PB6, PB7); //Left Pin, Right Pin
// MotorDriver motor2(PB8, PB9); //Left Pin, Right Pin

void setup()
{
  SerialCom.begin(9600);
}

void loop()
{
  // clk_time = pulseIn(PB6, LOW);
  Serial.print("CLK (A) pulse duration (us):");
  Serial.println(clk_time);
  

  delay(500);
}
