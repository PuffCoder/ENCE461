/* File:   racer.c
   Author: John Elliott, Heng Yin
   Date:   18 May 2023
   Descr:  Main system code.
*/

#include "target.h"
#include "button.h"
#include "led.h"
#include "pio.h"
#include "mcu.h"
#include "pacer.h"
#include "usb_serial.h"
#include "panic.h"
#include "radio_freq.h"
#include "delay.h"
#include "motors.h"
#include "motor_radio.h"
#include "radio_funct.h"
#include "bumper.h"
#include "radio_sm_racer.h"
#include "ledstrip.h"
#include "extint.h"
#include "battery_monitor.h"

#define PACER_WAIT 500
#define MOTOR_POLL_RATE 100
#define LED_POLL 25
#define HIGH 1
#define LOW 0

#ifndef LED_ACTIVE
#define LED_ACTIVE 0
#endif


static const button_cfg_t button_1_cfg = 
{
	.pio = BUTTON_PIO4,
	.pull_res = PIO_PULLDOWN
};

static const button_cfg_t button_sleep_cfg =
{
    .pio = BUTTON_SLEEP,
    .pull_res = PIO_PULLUP
};

button_t button_1;
button_t button_sleep;

void init_main(void)
{
    
    // Redirect stdio to USB serial
    usb_serial_stdio_init ();

    // Pacer Initialisation
    pacer_init (PACER_WAIT);

    // Bumper Config
    pio_config_set (BUMP_PIO, PIO_INPUT);

    // Config Debugging LEDs
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_LOW);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_LOW);

    pio_config_set (BUTTON_PIO4, PIO_PULLDOWN);
   

    pio_config_set(H_BRIDGE_SLEEP, PIO_OUTPUT_HIGH);

    if  (!radio_init()) {
        panic(LED_ERROR_PIO, ERROR_SLOW);
    }

    pio_output_set (LED_ERROR_PIO, !LED_ACTIVE);
    pio_output_set (LED_STATUS_PIO, !LED_ACTIVE);

    button_1 = button_init (&button_1_cfg);

    //sleep init
    button_sleep = button_init (&button_sleep_cfg);
    button_poll_count_set (BUTTON_POLL_COUNT (30));

    motor_init();
    
    ledstrip_init();
    rainbow_init();

    // Battery Voltage Detection Initisalisation
    bool bat_adc_inited = battery_monitor_init();
    if (! bat_adc_inited) {
        panic (LED_ERROR_PIO, ERROR_FAST);
    }
}
        


void uninit_main(void)
{
    radio_turn_off();
    ledstrip_clear_all();
    pio_output_set (H_BRIDGE_SLEEP, LOW);

}

void reinit_main(void)
{
    radio_turn_on();
    rainbow_init();
    pio_output_set (H_BRIDGE_SLEEP, HIGH);
}

void low_power_mode(void)
{

    uninit_main();

    while(!pio_input_get(BUTTON_SLEEP)) {
        continue;

    }

    while(pio_input_get(BUTTON_SLEEP)) {
        pio_output_set(LED_ERROR_PIO, LED_ACTIVE);
        delay_ms(5);
        pio_output_set(LED_ERROR_PIO, LED_ACTIVE);
        delay_ms(150);
    }

    reinit_main();
}




int main(void)
{
    mcu_jtag_disable();
    init_main();

    int ticks = 0;
    int led_ticks = 0;
   
    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait ();
        poll_battery();

        ticks++;
        led_ticks++;
        
        if (ticks >= PACER_WAIT / MOTOR_POLL_RATE)
        {
            ticks = 0;

            radio_state_machine();  

            if (button_poll (button_sleep) == BUTTON_STATE_PUSHED) {
                pio_output_set(LED_STATUS_PIO, LED_ACTIVE);
                low_power_mode();
            } else if (!check_battery_ok()) {
                low_power_mode();
            } else {
                pio_output_set(LED_STATUS_PIO, !LED_ACTIVE);
                pio_output_set(LED_ERROR_PIO, !LED_ACTIVE);
            }
        }

        if (led_ticks >= PACER_WAIT / LED_POLL)
        {
            led_ticks = 0;
            
            if (get_bumper()) {
                ledstrip_set_all(140,0,0); // Light Red.
            } else {
                ledstrip_rainbow();
            }
        }


    }
}