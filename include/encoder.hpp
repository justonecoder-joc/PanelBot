#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <HardwareSerial.h>

extern HardwareSerial SerialCom;

class Encoder
{
    public:
        Encoder(uint8_t tick_pin, uint32_t update_time);
        void update(uint32_t time_stamp);
        
        
        static Encoder *instance; // Needs to be public for definition/initialization in global scope.
        float rpm = 0;
        float velocity = 0;
        uint32_t ticks = 0;


    private:
    // ISRs must be static or global, since it is a callback function trigerred by hardware.
    // However, being a static function means that it cannot access "instance variables" using "this" pointer.
    // But, to mitigate this, the instance member that needs to be accessed can be declared as static as well.

        static void FallingEdgeISR();  // Static ISR function for falling edge interrupt
        void handleFallingEdge();  // Non-static function for handling falling edge
        void bubble_sort(float arr[], int n);
        
        uint32_t read_count = 0;
        float rpm_arr[8];
        float update_time_ms_i;
        uint32_t c_time = 0; // timestamp for rpm calculations.
        uint32_t p_time = 0; // timestamp for debouncing ticks.
        uint8_t tick_pin_i;
};
