/** @file   led.c
    @author M. P. Hayes, UCECE
    @date   08 June 2002
    @brief  Simple LED driver.
*/

#include "led.h"

/* These routines are for controlling a LED, piezoelectric tweeter, or
   any other 1 bit device.  The flashing code is now in flasher.c.  It
   is assumed that the LEDs are wired to ground so turn on with a
   logic high output level.  */


/** Create a new LED device and ensure LED off.  */
led_t
led_init (const led_cfg_t *cfg)
{
    pio_config_set (cfg->pio, cfg->active ? PIO_OUTPUT_LOW : PIO_OUTPUT_HIGH);

    return cfg;
}

// *************************   Student Code *************************
/** @file led.h
    @author Heng Yin
    @date 14 May 2023
    @brief LED component
    @note 
*/
void WR_led_init(void)
{
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
    pacer_init (10);  // waitting for LED init
}


