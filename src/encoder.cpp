#include "encoder.hpp"

Encoder* Encoder::instance = nullptr; // Static members need to be defined outside of the class definition.
                                      // They can only be declared inside the class.

Encoder::Encoder(uint8_t tick_pin, uint32_t update_time_ms)
{
    Encoder::instance = this;

    tick_pin_i = tick_pin;
    update_time_ms_i = update_time_ms;

    pinMode(tick_pin_i, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(tick_pin_i), Encoder::RisingEdgeISR, RISING); // Rising-edge interrupts for the tick pin.
    p_time = millis();
}

void Encoder::update(uint32_t time_stamp)
{
    c_time = time_stamp;
    if ((c_time - p_time) > update_time_ms_i)
    {
        rpm = float(ticks / 64.0f) * 60000 / update_time_ms_i; // 20 ticks = 1 revolution.
        velocity = rpm / 60 * 2 * PI * 0.0381f;
        // SerialCom.print("RPM = ");
        // SerialCom.print(rpm);
        // SerialCom.print(", Velocity = ");
        // SerialCom.print(velocity);
        // SerialCom.print(", ticks = ");
        // SerialCom.println(ticks);

        ticks = 0;
        p_time = c_time; // Because ticks may still be read when calulations are being performed.
    }
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
