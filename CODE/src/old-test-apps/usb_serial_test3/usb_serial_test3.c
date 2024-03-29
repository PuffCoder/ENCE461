#include <stdio.h>
#include "usb_serial.h"
#include "pio.h"
#include "sys.h"
#include "pacer.h"
#include "delay.h"


#define PACER_RATE 1000
#define LED_FLASH_RATE 2

static usb_serial_cfg_t usb_serial_cfg =
{
    .read_timeout_us = 1,
    .write_timeout_us = 1,
};

static usb_serial_t *usb_serial;


static void
prompt_command (void)
{
    usb_serial_puts (usb_serial, "> ");
}


static void
process_command (void)
{
    char buffer[80];
    char *str;

    str = usb_serial_gets (usb_serial, buffer, sizeof (buffer));
    if (! str)
        return;

    // usb_serial (usb_serial, "<<<%s>>>\n", str);

    switch (str[0])
    {
    case '0':
        pio_output_set (LED_ERROR_PIO, 0);
        break;

    case '1':
        pio_output_set (LED_ERROR_PIO, 1);
        break;

    case 'h':
        usb_serial_puts (usb_serial, "Hello world!\n");
        break;

    default:
       break;
    }

    prompt_command ();
}


int main (void)
{
    usb_cdc_t usb_cdc;
    int flash_ticks = 0;
    int i;

    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);

    // Create non-blocking tty device for USB CDC connection.
    usb_serial = usb_serial_init (&usb_serial_cfg, "");

    for (i = 0; i < 100; i++)
    {
        delay_ms (100);
        usb_serial_puts (usb_serial, "Hello world\n");
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
