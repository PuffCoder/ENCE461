#include <pio.h>
#include "target.h"
#include "pacer.h"
#include "led.h"
// #include "./CarLib/carled.h"

#define LED_FLASH_RATE 2

// #define led_t state->pio PA31_PIO
// #define led_t state->active 1.
// Define a led_cfg_t structure with the desired configuration

// void InitEachComponent();
// led_t Init_LED(void);


int main(void)
{

  led_t myLED = Init_LED();
  LED_TurnOn(myLED);

  while(1)
  {
    pacer_wait();

  }
  return 0;
}

