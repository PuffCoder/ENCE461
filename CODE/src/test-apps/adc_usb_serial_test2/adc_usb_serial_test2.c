/* File:   adc_usb_serial_test2.c
   Author: M. P. Hayes, UCECE
   Date:   3 May 2021
   Descr:  This reads from joystick ADC channels.
           It triggers ADC conversions as each sample is read.
*/
#include <stdio.h>
#include "usb_serial.h"
#include "adc.h"
#include "pacer.h"
#include "panic.h"

#define PACER_RATE 2

static const adc_cfg_t adc_cfg =
{
    .bits = 12,
    .channels = BIT (JOYSTICK_X_ADC_CHANNEL) | BIT (JOYSTICK_Y_ADC_CHANNEL),
    .trigger = ADC_TRIGGER_SW,
    .clock_speed_kHz = 1000
};


int main (void)
{
    adc_t adc;
    int count = 0;

    // Redirect stdio to USB serial
    usb_serial_stdio_init ();

    adc = adc_init (&adc_cfg);
    if (! adc)
        panic (LED_ERROR_PIO, 1);

    pacer_init (PACER_RATE);
    while (1)
    {
        uint16_t data[2];

        pacer_wait ();

        // The lowest numbered channel is read first.
        adc_read (adc, data, sizeof (data));

        printf ("%3d: %d, %d\n", count, data[0], data[1]);
    }
}
