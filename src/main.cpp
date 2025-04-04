#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include "proximity_sensor.hpp"
#include "limit_switch.hpp"
#include "motor_driver.hpp"
#include "encoder.hpp"
#include "PID.hpp"
#include "solenoid_valve.hpp"

#define UPDATE_TIME_MS 100 // millisecondss. update interval.
#define DT_MS 100 // PID update time.

// #define DISTANCE_THRESHOLD 1947.6 // mm
// #define WIDTH_THRESHOLD (w / 2)

// bool bidirectional_mode = true;
// bool direction_movement = true; // forward = true, backward = false

// Driver Initializations.
HardwareSerial SerialCom(PA10, PA9);

MotorDriver mob_motor1(PA6, PA7);  // Left Pin, Right Pin
MotorDriver mob_motor2(PB0, PB1);  // Left Pin, Right Pin
// MotorDriver brush_motor(PA2, PA3); // Left Pin, Right Pin

LimitSwitch limitSwitch1(PB10);
LimitSwitch limitSwitch2(PB11);
ProximitySensor proximitySensor1(PB4);
ProximitySensor proximitySensor2(PB5);

Encoder encoder1(PB6, 100); // A 2 Hz RPMS calculation interval produced the best results.
// Encoder encoder2(PB7, UPDATE_TIME_MS); // A 2 Hz RPMS calculation interval produced the best results.

SolenoidValve valve1(PB3);
SolenoidValve valve2(PA15);

// Constants.
float mob1_speed = 0.0f;
float mob2_speed = 0.0f;
uint32_t prev_time;
uint32_t delta_time_ms = 50;


// Temporary.
uint32_t count = 0;

PID_Controller pid_mob1(2.0f, 0.1f, 0.1f, 0.0f, 1.0f);
PID_Controller pid_mob2(2.0f, 0.1f, 0.1f, 0.0f, 1.0f);

uint32_t time_stamp = 0;


void setup()
{
    SerialCom.begin(115200);
    // brush_motor.set_direction(Forward); // Backward == Right
    mob_motor1.set_direction(Forward);  // Forward == Left
    mob_motor2.set_direction(Forward); // Backward == Right
    prev_time = millis();
}

void loop()
{
  time_stamp = millis();
  encoder1.update(time_stamp);
  // encoder2.update(time_stamp);
  

  mob_motor1.set_speed(0.5);

  if (count == 1)
  {
    SerialCom.print("Encoder 1 Velocity: ");
    SerialCom.print(encoder1.velocity);
    SerialCom.print(", RPM = ");
    SerialCom.print(encoder1.rpm);
    SerialCom.print(", ticks = ");
    SerialCom.println(encoder1.ticks);
    // SerialCom.print("Encoder 2 Velocity: ");
    // SerialCom.println(encoder2.velocity);
    count = 0;
  }

  if ((time_stamp - prev_time) > delta_time_ms)
  {
  // //   mob1_speed = pid_mob1.calculate(0.14, encoder1.velocity, float(delta_time_ms)/1000);
  // //   mob2_speed = pid_mob2.calculate(0.14, encoder2.velocity, float(delta_time_ms)/1000);
    
  // //   mob_motor1.set_speed(mob1_speed);
  // //   mob_motor2.set_speed(mob2_speed);
    
    prev_time = time_stamp;
    count++;
  }

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



  // delay(10);
}
