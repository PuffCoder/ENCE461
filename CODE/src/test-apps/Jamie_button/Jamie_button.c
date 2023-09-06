/* File:   button_test1.c
   Author: M. P. Hayes, UCECE + Jamie
   Date:   18 Dec 2021
   Descr:  Simple button test demo without debouncing, printing to usb serial
*/

#include "mcu.h"
#include "pio.h"
#include "pacer.h"
#include "usb_serial.h"

#define PACER_RATE 100

int
main (void)
{
    usb_serial_stdio_init ();

    /* Configure LED PIO as output.  */
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);

    /* Configure button PIO as input with pulldown.  */
    pio_config_set (BUTTON_PIO, PIO_PULLDOWN);

    pacer_init (PACER_RATE);

    uint32_t usb_print = 0;
    uint32_t count = 0;

    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait ();

        usb_print++;
        count++;

        if (pio_input_get (BUTTON_PIO))
        {
            pio_output_high (LED_STATUS_PIO);
            pio_output_high (LED_ERROR_PIO);
            if (count > 50)
            {
                count = 0;
                printf ("BUTTON ON (%ld)\n", usb_print);
            }
        }
        else
        {
          pio_output_low (LED_STATUS_PIO);
          pio_output_low (LED_ERROR_PIO);
          if (count > 50)
            {
                count = 0;
                printf ("button off (%ld)\n", usb_print);
            }
        }
        if (usb_print > 1000)
        {
            usb_print = 0;
        }
    }

}
