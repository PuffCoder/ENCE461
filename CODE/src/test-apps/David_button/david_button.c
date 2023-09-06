/* File:   button_test1.c
   Author: M. P. Hayes, UCECE
   Date:   18 Dec 2021
   Descr:  Simple button test demo without debouncing
*/
// TEST for SW1 : PA6
#include "mcu.h"
#include "pio.h"
#include "pacer.h"

#define PACER_RATE 100
// #define BLED PA17_PIO

int
main (void)
{
    /* Configure LED PIO as output.  */
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);
    // pio_config_set (BLED, PIO_OUTPUT_HIGH);
          pio_config_set (BLED, PIO_OUTPUT_LOW);

    /* Configure button PIO as input with pullup.  */
    // pio_config_set (BUTTON_PIO3, PIO_PULLUP);
    pio_config_set (BUTTON_PIO3, PIO_PULLUP);
    pio_config_set (BUTTON_PIO4, PIO_PULLUP);

    pacer_init (PACER_RATE);

    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait ();

        if (pio_input_get (BUTTON_PIO4 ))
        // if (pio_input_get (SW2))
        {
          // pio_config_set (BLED, PIO_OUTPUT_LOW);
          // pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
          // pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);
            // pio_output_high (LED_STATUS_PIO);
            // pio_output_high (LED_ERROR_PIO);
          pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
          pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
        }
        else if (pio_input_get( BUTTON_PIO3))
        {
          pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
          pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);

          // pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
          // pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
            // pio_output_low (LED_STATUS_PIO);
            // pio_output_low (LED_ERROR_PIO);
        }
        else 
        {
          
          pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
          pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);
        }
    }

}
