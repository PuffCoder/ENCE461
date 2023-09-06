/* File:   button_test1.c
   Author: M. P. Hayes, UCECE
   Date:   18 Dec 2021
   Descr:  Simple button test demo without debouncing
*/

#include "mcu.h"
#include "pio.h"
#include "pacer.h"

#define PACER_RATE 100

int
main (void)
{
    /* Configure LED PIO as output.  */
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);

    /* Configure button PIO as input with pulldown.  */
    pio_config_set (BUTTON_PIO, PIO_PULLDOWN);

    pacer_init (PACER_RATE);

    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait ();

        if (pio_input_get (BUTTON_PIO))
        {
            pio_output_high (LED_STATUS_PIO);
            pio_output_high (LED_ERROR_PIO);
        }
        else
        {
          pio_output_low (LED_STATUS_PIO);
          pio_output_low (LED_ERROR_PIO);
        }
    }

}
