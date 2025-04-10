#include "encoder.hpp"

Encoder* Encoder::instance = nullptr; // Static members need to be defined outside of the class definition.
                                      // They can only be declared inside the class.

Encoder::Encoder(uint8_t tick_pin, uint32_t update_time_ms)
{
    Encoder::instance = this;

    tick_pin_i = tick_pin;
    update_time_ms_i = update_time_ms;

    pinMode(tick_pin_i, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(tick_pin_i), Encoder::FallingEdgeISR, FALLING); // Rising-edge interrupts for the tick pin.
    p_time = millis();
}

void Encoder::update(uint32_t time_stamp)
{
    c_time = time_stamp;
    if ((c_time - p_time) > update_time_ms_i)
    {
        float rpm_temp = float(ticks / 64.0f) * 60000 / update_time_ms_i; // 20 ticks = 1 revolution.
        this->rpm_arr[read_count] = rpm_temp;

        // SerialCom.print("Ticks = ");
        // SerialCom.println(ticks);

        this->ticks = 0;
        this->p_time = c_time; // Because ticks may still be read when calulations are being performed.
        this->read_count++;
    }

    if (this->read_count == 8)
    {
        bubble_sort(rpm_arr, 8);

        this->rpm = 0;
        for (int i = 2; i < 6; i++)
            this->rpm += rpm_arr[i];
        this->rpm /= 4;

        this->velocity = rpm / 60 * 2 * PI * 0.0381f;

        SerialCom.print("RPM = ");
        SerialCom.print(this->rpm);
        SerialCom.print(", Velocity = ");
        SerialCom.println(this->velocity);
        this->read_count = 0;
    }
}

// Static ISR function called on falling edge or tick_pin_i
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
    // uint32_t timestamp = millis();
    
    // if (timestamp - tick_timestamp > 10) // Ignore ticks for 10 ms. For debouncing.
    // {
        // Increment ticks on the falling edge
    // tick_timestamp = timestamp;
    this->ticks++;
    // }
}

void Encoder::bubble_sort(float arr[], int n)
{
  int i, j;

  for (i = 0; i < n-1; i++)
      for (j = 0; j < n-i-1; j++)
          if (arr[j] > arr[j+1])
          {
            float temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
          }
}
