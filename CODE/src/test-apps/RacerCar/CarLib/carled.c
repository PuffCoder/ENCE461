#include "carled.h"

void LED_TurnOff(led_t led)
{
  pio_output_high(led->pio);
}

void LED_TurnOn(led_t led)
{
  pio_output_low(led->pio);
}


