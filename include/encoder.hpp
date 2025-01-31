#pragma once

#include <Arduino.h>
#include <stdint.h>

class Encoder
{
    public:
        Encoder(uint8_t CLK_pin, uint8_t SW_pin, uint32_t timer_frequency = 10,  TIM_TypeDef *timer = TIM2);
        // void update(); // Update ticks;
        ~Encoder();
        
        static Encoder *instance; // Needs to be public for definition/initialization in global scope.
        float rpm = 0;
        uint32_t ticks = 0;


    private:
    // ISRs must be static or global, since it is a callback function trigerred by hardware.
    // However, being a static function means that it cannot access "instance variables" using "this" pointer.
    // . But, to mitigate this, the instance member that needs to be accessed can be declared as static as well.
        static void TimerISR();
        void handleTimerISR(); // Update rpm.

        static void FallingEdgeISR();  // Static ISR function for falling edge interrupt
        void handleFallingEdge();  // Non-static function for handling falling edge

        HardwareTimer *interval_timer;


        float timer_f;
        uint32_t tick_timestamp = 0; // timestamp for debouncing ticks.
        uint32_t prev_ticks = 0;
        uint8_t CLK_pin_i;
        uint8_t SW_pin_i;
};
