#include "encoder.hpp"

Encoder* Encoder::instance = nullptr; // Static members need to be defined outside of the class definition.
                                      // They can only be declared inside the class.

Encoder::Encoder(uint8_t CLK_pin, uint8_t SW_pin, uint32_t timer_frequency,  TIM_TypeDef *timer)
{
    Encoder::instance = this;

    CLK_pin_i = CLK_pin;
    SW_pin_i = SW_pin;
    timer_f = timer_frequency;

    pinMode(CLK_pin_i, INPUT_PULLUP);
    pinMode(SW_pin_i, INPUT_PULLUP);

    interval_timer = new HardwareTimer(timer); // The timer that we will use for rpm calculation intervals.

    interval_timer->setOverflow(timer_frequency, HERTZ_FORMAT);  // Set frequency to 10 Hz (100 ms interval)
    interval_timer->attachInterrupt(Encoder::TimerISR); // Attach interrupt handler
    interval_timer->resume();                   // Start the timer

    attachInterrupt(digitalPinToInterrupt(CLK_pin_i), Encoder::FallingEdgeISR, FALLING);
}

void Encoder::TimerISR()
{
    if (Encoder::instance)
    {
        Encoder::instance->handleTimerISR();
    }
}

void Encoder::handleTimerISR()
{
    rpm = (float) (ticks - prev_ticks) * timer_f / 20.0f * 60; // 20 ticks = 1 revolution.
    velocity = rpm / 60 * 2 * 3.142f * 0.0381f;
    prev_ticks = ticks;
}

// Static ISR function called on falling edge or CLK_pin_i
void Encoder::FallingEdgeISR()
{
    // noInterrupts();
    if (Encoder::instance)
    {
        Encoder::instance->handleFallingEdge();  // Delegate to the instance's method
    }
    // interrupts();
}

// Non-static function to handle the falling edge event
void Encoder::handleFallingEdge()
{
    uint32_t timestamp = millis();
    
    if (timestamp - tick_timestamp > 2) // Ignore ticks for 2 ms
    {
        // Increment ticks on the falling edge
        tick_timestamp = timestamp;
        this->ticks++;
    }
}

Encoder::~Encoder()
{
    interval_timer->pause();
    delete interval_timer;
}
