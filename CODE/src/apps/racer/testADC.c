/* File:   racer.c
   Author: John Elliott, Heng Yin
   Date:   18 May 2023
   Descr:  Main system code.
*/

#include "target.h"
#include "button.h"
#include "led.h"
#include "pio.h"
#include "mcu.h"
#include "pacer.h"
#include "usb_serial.h"
#include "panic.h"
#include "radio_freq.h"
#include "delay.h"
#include "motors.h"
#include "motor_radio.h"
#include "radio_funct.h"
#include "circ_buff.h"
#include "battery_monitor.h"

#define PACER_WAIT 500
#define MOTOR_POLL_RATE 100
#define ERROR_FAST 1
#define ERROR_MED 2
#define ERROR_SLOW 3

#ifndef LED_ACTIVE
#define LED_ACTIVE 0
#endif

// ******************************************************
// // in the main loop;
//   bool IsBatt = 0;
//   IsBatt =  battery_monitor_init();
//   double battV= 0.0;

// // in the while loop
//   battV= adc_send();
//   printf("%f\n",battV); 
// *****************************************************

int main(void)
{
    // Redirect stdio to USB serial
    /* usb_serial_stdio_init (); */

    // Pacer Initialisation
    pacer_init (10);

  /* bool IsBatt = 0; */
  /* IsBatt =  battery_monitor_init(); */
  /* bool lowBatt = 0; */
  
  /* double battV= 0.0; */
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (BUMP_PIO,PIO_INPUT);
    while (1)
    {
        /* Wait until next clock tick.  */

        pacer_wait ();
    if (pio_input_get(BUMP_PIO))
      pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    else

      pio_config_set(LED_ERROR_PIO,PIO_OUTPUT_LOW);
        /* batt_States(); */
        
    }
}
