#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include "proximity_sensor.hpp"
#include "limit_switch.hpp"
#include "motor_driver.hpp"
#include "encoder.hpp"
#include "PID.hpp"
#include "solenoid_valve.hpp"

#define UPDATE_TIME_MS 100 // microseconds.

HardwareSerial SerialCom(PA10, PA9);

MotorDriver mob_motor1(PA6, PA7);  // Left Pin, Right Pin
MotorDriver mob_motor2(PB0, PB1);  // Left Pin, Right Pin
MotorDriver brush_motor(PA2, PA3); // Left Pin, Right Pin

LimitSwitch limitSwitch1(PB10);
LimitSwitch limitSwitch2(PB11);
ProximitySensor proximitySensor1(PB4);
ProximitySensor proximitySensor2(PB5);


Encoder encoder1(PB6, UPDATE_TIME_MS); // A 2 Hz RPMS calculation interval produced the best results.
// Encoder encoder2(PB7, NULL, 2, TIM4); // A 2 Hz RPMS calculation interval produced the best results.

SolenoidValve valve1(PB3);
SolenoidValve valve2(PA15);

float mob1_speed = 0.0f;
float mob2_speed = 0.0f;
// float brush_speed = 0.0f;

// float delta_time = 100e-3;

PID_Controller pid_mob1(2.0f, 0.1f, 0.1f, 0.0f, 1.0f);
PID_Controller pid_mob2(2.0f, 0.1f, 0.1f, 0.0f, 1.0f);

// uint32_t time_stamp = 0;

// #define DISTANCE_THRESHOLD 1947.6 // mm
// #define WIDTH_THRESHOLD (w / 2)

// bool bidirectional_mode = true;
// bool direction_movement = true; // forward = true, backward = false

void setup()
{
    SerialCom.begin(115200);
    // brush_motor.set_direction(Forward); // Backward == Right
    // mob_motor1.set_direction(Forward);  // Forward == Left
    // mob_motor2.set_direction(Backward); // Backward == Right

    // time_stamp = millis();
}

void loop()
{
  encoder1.update();
//   Serial.println(encoder1.rpm)
//   // limitSwitch.sense();
//   // proximitySensor.sense();
//   valve1.turnOn();
//   SerialCom.print("Valve state");
//   SerialCom.println(valve1.getState());
//   delay(1000);
//   valve1.turnOff();
//   SerialCom.print("Valve state");
//   SerialCom.println(valve1.getState());
//   delay(1000);

//   uint32_t current_time = millis();

  //a Print with a delay of 500 ms.
//   if ((current_time - time_stamp) > 500)
//   {
// SerialCom.print("PID output: ");
// SerialCom.println(mob2_speed);  

// SerialCom.print("RPM: ");
// SerialCom.println(encoder1.rpm);

// SerialCom.print("Average Velocity: ");
// SerialCom.println(encoder1.velocity);

// SerialCom.print("Ticks: ");
// SerialCom.println(encoder1.ticks);
// delay(500);
//   }

  // if ((current_time - time_stamp) > 50)
  // {
  //   mob1_speed = pid_mob1.calculate(0.14, encoder1.velocity, delta_time);
  //   mob2_speed = pid_mob2.calculate(0.14, encoder2.velocity, delta_time);
    
  //   mob_motor1.set_speed(mob1_speed);
  //   mob_motor2.set_speed(mob2_speed);
    
  //   time_stamp = current_time;
  // }

  // delay(10);
}
