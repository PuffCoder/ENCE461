/* File:   usb_vbus_test1.c
   Author: M. P. Hayes, UCECE
   Date:   15 May 2007
   Descr:  Turn on LED if USB connected
*/
#include <pio.h>
#include "target.h"
#include "pacer.h"

/* Define how fast ticks occur.  This must be faster than
   TICK_RATE_MIN.  */
#define LOOP_POLL_RATE 200

/* Define LED flash rate in Hz.  */
#define LED_FLASH_RATE 2

#ifndef UDP_VBUS_PIO
#define UDP_VBUS_PIO BUTTON_PIO
#endif

int
main (void)
{
    uint8_t flash_ticks;

    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);
    pio_config_set (UDP_VBUS_PIO, PIO_INPUT);

    pacer_init (LOOP_POLL_RATE);
    flash_ticks = 0;

    while (1)
    {
	pacer_wait ();

        // Turn on error LED if VBUS not detected
        pio_output_set (LED_ERROR_PIO, ! pio_input_get (UDP_VBUS_PIO));

        // Flash status LED
	flash_ticks++;
	if (flash_ticks >= LOOP_POLL_RATE / (LED_FLASH_RATE * 2))
	{
	    flash_ticks = 0;
	    pio_output_toggle (LED_STATUS_PIO);
	}
    }
}
