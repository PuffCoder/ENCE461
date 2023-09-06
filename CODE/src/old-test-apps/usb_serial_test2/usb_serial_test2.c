#include <stdio.h>
#include "usb_serial.h"
#include "pio.h"
#include "sys.h"
#include "pacer.h"
#include "delay.h"


#define PACER_RATE 1000
#define LED_FLASH_RATE 2

static FILE *stream;


static void
prompt_command (void)
{
    fprintf (stream, "> ");
    fflush (stream);
}


static void
process_command (void)
{
    char buffer[80];
    char *str;

    str = fgets (buffer, sizeof (buffer), stream);
    if (! str)
        return;

    // fprintf (stream, "<<<%s>>>\n", str);

    switch (str[0])
    {
    case '0':
        pio_output_set (LED_ERROR_PIO, 0);
        break;

    case '1':
        pio_output_set (LED_ERROR_PIO, 1);
        break;

    case 'h':
        fprintf (stream, "Hello world!\n");
        fflush (stdout);
        break;

    default:
       break;
    }

    prompt_command ();
}


int main (void)
{
    int flash_ticks = 0;
    int i;

    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);

    // Redirect stdio to USB serial
    usb_serial_stdio_init ();

    for (i = 0; i < 100; i++)
    {
        fprintf (stream, "Hello world %d\n", i);
        fflush (stream);
        delay_ms (100);
    }

    prompt_command ();

    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();

	flash_ticks++;
	if (flash_ticks >= PACER_RATE / (LED_FLASH_RATE * 2))
	{
	    flash_ticks = 0;

	    pio_output_toggle (LED_STATUS_PIO);

            process_command ();
	}
    }
}
