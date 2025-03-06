#include "encoder.hpp"

Encoder* Encoder::instance = nullptr; // Static members need to be defined outside of the class definition.
                                      // They can only be declared inside the class.

Encoder::Encoder(uint8_t tick_pin, uint32_t timer_frequency,  TIM_TypeDef *timer)
{
    Encoder::instance = this;

    tick_pin_i = tick_pin;
    timer_f = timer_frequency;

    pinMode(tick_pin_i, INPUT_PULLUP);

    interval_timer = new HardwareTimer(timer); // The timer that we will use for rpm calculation intervals.

    interval_timer->setOverflow(timer_frequency, HERTZ_FORMAT);  // Set frequency to 10 Hz (100 ms interval)
    interval_timer->attachInterrupt(Encoder::TimerISR); // Attach timer interrupt handler
    interval_timer->resume();                   // Start the timer

    attachInterrupt(digitalPinToInterrupt(tick_pin_i), Encoder::RisingEdgeISR, RISING); // Rising-edge interrupts for the tick pin.
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
    rpm = float(ticks * timer_f) / 64.0f * 60; // 20 ticks = 1 revolution.
    // velocity = rpm / 60 * 2 * 3.142f * 0.0381f;
    SerialCom.print("RPM = ");
    SerialCom.print(rpm);
    SerialCom.print(", ticks = ");
    SerialCom.println(ticks);

    ticks = 0;
}

// Static ISR function called on falling edge or tick_pin_i
void Encoder::RisingEdgeISR()
{
    // noInterrupts();
    if (Encoder::instance)
    {
        Encoder::instance->handleRisingEdge();  // Delegate to the instance's method
    }
    // interrupts();
}

// Non-static function to handle the falling edge event
void Encoder::handleRisingEdge()
{
    // uint32_t timestamp = millis();
    
    // if (timestamp - tick_timestamp > 10) // Ignore ticks for 10 ms. For debouncing.
    // {
        // Increment ticks on the falling edge
    // tick_timestamp = timestamp;
    this->ticks++;
    // }
}

Encoder::~Encoder()
{
    interval_timer->pause();
    delete interval_timer;
}
