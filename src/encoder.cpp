#include "encoder.hpp"

Encoder* Encoder::instance = nullptr; // Static members need to be defined outside of the class definition.
                                      // They can only be declared inside the class.

Encoder::Encoder(uint8_t CLK_pin, uint8_t SW_pin = -1, TIM_TypeDef *timer, uint32_t timer_frequency)
{
    Encoder::instance = this;

    CLK_pin_i = CLK_pin;
    SW_pint_i = SW_pin;
    timer_f = timer_frequency;

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
    rpm = (float) (ticks - prev_ticks) * timer_f;
    prev_ticks = ticks;
}

// Static ISR function called on falling edge or CLK_pin_i
void Encoder::FallingEdgeISR()
{
    if (Encoder::instance)
    {
        Encoder::instance->handleFallingEdge();  // Delegate to the instance's method
    }
}

// Non-static function to handle the falling edge event
void Encoder::handleFallingEdge()
{
    // Increment ticks on the falling edge
    this->ticks++;
}

// void Encoder::update()
// {

// }

Encoder::~Encoder()
{
    interval_timer->pause();
    delete interval_timer;
}
