/* File:   adxl345_test1.c
   Author: M. P. Hayes, UCECE
   Date:   3 December 2022
   Descr:  Read from an ADXL345 accelerometer and write its output to the USB serial.
*/
#include "pio.h"
#include "delay.h"
#include "target.h"
#include "pacer.h"
#include "usb_serial.h"
#include "adxl345.h"
#include "panic.h"
#include "mcu.h"


/*
 * NOTE: you must define ADXL345_ADDRESS in target.h for this to compile.
 */
#ifndef ADXL345_ADDRESS
#error ADXL345_ADDRESS must be defined
#endif

#define PACER_RATE 20
#define ACCEL_POLL_RATE 1

#ifndef LED_ACTIVE
#define LED_ACTIVE PIO_OUTPUT_LOW
#endif

static twi_cfg_t adxl345_twi_cfg =
{
    .channel = TWI_CHANNEL_0,
    .period = TWI_PERIOD_DIVISOR (100000), // 100 kHz
    .slave_addr = 0
};


int
main (void)
{
    mcu_jtag_disable ();
    twi_t adxl345_twi;
    adxl345_t *adxl345;
    int ticks = 0;
    int count = 0;

    // Redirect stdio to USB serial
    usb_serial_stdio_init ();

    pio_config_set (LED_ERROR_PIO, LED_ACTIVE);
    pio_output_set (LED_ERROR_PIO, ! LED_ACTIVE);
    pio_config_set (LED_STATUS_PIO, LED_ACTIVE);
    pio_output_set (LED_STATUS_PIO, ! LED_ACTIVE);

    // Initialise the TWI (I2C) bus for the ADXL345
    adxl345_twi = twi_init (&adxl345_twi_cfg);

    if (! adxl345_twi)
        panic (LED_ERROR_PIO, 1);

    // Initialise the ADXL345
    adxl345 = adxl345_init (adxl345_twi, ADXL345_ADDRESS);

    if (! adxl345)
        panic (LED_ERROR_PIO, 2);

    pacer_init (PACER_RATE);

    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait ();

        ticks++;
        if (ticks < PACER_RATE / ACCEL_POLL_RATE)
            continue;
        ticks = 0;

        pio_output_toggle (LED_STATUS_PIO);

        /* Read in the accelerometer data.  */
        if (! adxl345_is_ready (adxl345))
        {
            count++;
            printf ("Waiting for accelerometer to be ready... %d\n", count);
        }
        else
        {
            int16_t accel[3];
            if (adxl345_accel_read (adxl345, accel))
            {
                printf ("x: %5d  y: %5d  z: %5d\n", accel[0], accel[1], accel[2]);
            }
            else
            {
                printf ("ERROR: failed to read acceleration\n");
            }
        }
    }
}
