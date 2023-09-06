/* File:   buzzer_test1.c
   Author: Jamie Thomas
   Date:   2 May 2023
   Descr:  Simple buzzer test demo
*/

#include "mcu.h"
#include "pio.h"
#include "pacer.h"
#include "delay.h"

#define PACER_RATE 100

// PS1240P02BT

int main(void)
{
    mcu_jtag_disable ();

    /* Configure LED PIO as output.  */
    pio_config_set(LED_STATUS_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(BUZZER_PIO, PIO_OUTPUT_HIGH);

    /* Configure button PIO as input with pulldown.  */
    pio_config_set(BUTTON_PIO, PIO_PULLDOWN);

    pacer_init(PACER_RATE);
    int ontime = 7;

    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait();

        if (pio_input_get(BUTTON_PIO))
        {
            delay_ms (ontime);
            pio_output_toggle (LED_STATUS_PIO);
            pio_output_high(BUZZER_PIO);
            delay_ms (10-ontime);
            pio_output_low(BUZZER_PIO);
        }
        else
        {
            pio_output_high(LED_STATUS_PIO);
            pio_output_low(BUZZER_PIO);
        }
    }
}
