#include "target.h"
#include "button.h"
#include "led.h"
#include "pio.h"
#include "adxl_data.h"
#include "mcu.h"
#include "pacer.h"
#include "usb_serial.h"
#include "panic.h"
#include "radio_freq.h"
#include "delay.h"
#include "radio_funct.h"
#include "radio_hat.h"
#include "radio_sm_hat.h"
#include "buzzer.h"
#include "extint.h"
#include "ledstrip.h"
#include "battery_monitor.h"




#define PACER_WAIT 500
#define ACCEL_POLL_RATE 25

#ifndef LED_ACTIVE
#define LED_ACTIVE 0
#endif


void sleep_button_handler(void)
{
    /*
    uint32_t irq_reg = pio_irq_clear(BUTTON_SLEEP);
    

    static bool is_sleep = false;

    if (irq_reg && PIO_BITMASK_ (BUTTON_SLEEP)) {
        if (is_sleep)
        {
            is_sleep = ! is_sleep;
        }
        else
        {
            is_sleep = ! is_sleep;
            cpu_wfi();
        }
    }
    */
    

    
    
}

extint_cfg_t sleep_cfg = 
{
    BUTTON_SLEEP,
    &sleep_button_handler
};

static const button_cfg_t button_1_cfg =
{
    .pio = BUTTON_PIO,
    .pull_res = PIO_PULLDOWN
};

static const button_cfg_t button_2_cfg =
{
    .pio = BUTTON_2_PIO,
    .pull_res = PIO_PULLDOWN
};

static const button_cfg_t button_sleep_cfg =
{
    .pio = BUTTON_SLEEP,
    .pull_res = PIO_PULLUP
};

button_t button_1;
button_t button_2;
button_t button_sleep;

void init_everything(void)
{
    // Redirect stdio to USB serial
    usb_serial_stdio_init ();

    // Pacer Initialisation
    pacer_init (PACER_WAIT);

    // Config Debugging LEDs
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    pio_output_set (LED_ERROR_PIO, ! LED_ACTIVE);
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
    pio_output_set (LED_STATUS_PIO, ! LED_ACTIVE);

    // Accelerometer Initialisation
    bool adxl_check = accel_init();
    if (! adxl_check)
        panic (LED_ERROR_PIO, 4);


    // Radio Initialisation
    bool radio_check = radio_init ();
    if (! radio_check)
        panic (LED_ERROR_PIO, 3);

    // Buzzer Initialisation
    buzzer_init();
    button_1 = button_init (&button_1_cfg);
    button_2 = button_init (&button_2_cfg);

    //sleep init
    button_sleep = button_init (&button_sleep_cfg);
    button_poll_count_set (BUTTON_POLL_COUNT (30));

    // LED Strip Initialisation
    ledstrip_init();

    // Start Up Animation
    ledstrip_clear_all();
    ledstrip_set_section(200, 255, 0, SECTION_1);
    delay_ms(500);
    ledstrip_set_section(200, 100, 0, SECTION_2);
    delay_ms(500);
    ledstrip_set_section(255, 0, 0, SECTION_3);
    delay_ms(500);

    ledstrip_set_all(255, 255, 0);

    // Battery Voltage Detection Initisalisation
    bool bat_adc_inited = battery_monitor_init();
    if (! bat_adc_inited)
        panic (LED_ERROR_PIO, 6);
    

}


void uninit_everything(void)
{

    accel_deinit();

    radio_turn_off();

    ledstrip_clear_all();

    sleep_buzzer();

}

void reinit_everything(void)
{

    bool adxl_check = accel_init();
    if (! adxl_check)
        panic (LED_ERROR_PIO, 2);

    radio_turn_on();

    ledstrip_set_all(255, 255, 0);

    buzzer_init();


}

void low_power_mode(void)
{

    //static bool toggle = false;

    uninit_everything();

    while(!pio_input_get(BUTTON_SLEEP)) {

        continue;

    }

    while(pio_input_get(BUTTON_SLEEP)) {
        pio_output_set(LED_ERROR_PIO, LED_ACTIVE);
        delay_ms(5);
        pio_output_set(LED_ERROR_PIO, !LED_ACTIVE);
        delay_ms(150);

    }

    reinit_everything();

}

int main(void)
{
    mcu_jtag_disable ();
    
    int ticks = 0;

    init_everything();
    
    double battV= 0.0;

    while (1)
    {
        /* Wait until next clock tick.  */
        pacer_wait ();

        poll_accel ();

        poll_battery ();

        // IDK if this is useful atm. 
        ticks++;
        if (ticks >= PACER_WAIT / ACCEL_POLL_RATE)
        {
            ticks = 0;

            // pio_output_toggle (LED_STATUS_PIO);

            radio_state_machine();

            if (button_poll (button_1) == BUTTON_STATE_RELEASED)
            {
                pio_output_set(LED_STATUS_PIO, LED_ACTIVE);
                run_buzzer();
            }
            else if (button_poll (button_2) == BUTTON_STATE_RELEASED)
            {
                pio_output_set(LED_STATUS_PIO, LED_ACTIVE);
                run_buzzer_extended();
            }
            else
            {
                pio_output_set(LED_STATUS_PIO, !LED_ACTIVE);
            }


            // if (button_poll (button_sleep) == BUTTON_STATE_PUSHED) /* For USB power */
            if (button_poll (button_sleep) == BUTTON_STATE_PUSHED || !check_battery_ok()) /* For battery power, with low voltage detection */
            {

                low_power_mode();

            } else {
                pio_output_set(LED_STATUS_PIO, !LED_ACTIVE);
            }
            
        }
    }
}
