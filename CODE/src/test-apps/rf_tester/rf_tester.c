/* File:   rf_tester.c
   Author: A. Renaud
   Date:   Oct 2020
   Descr:  Software to run on the test boxes for NRF debugging
*/
#include <stdio.h>
#include "usb_serial.h"
#include "nrf24.h"
#include "adc.h"
#include "pio.h"
#include "pacer.h"
#include "panic.h"
#include "delay.h"
#include "button.h"

#define RADIO_CHANNEL 4
#define RADIO_ADDRESS 0x0123456789LL
#define RADIO_PAYLOAD_SIZE 32

#define TX_LED PA21_PIO
#define RX_LED PA31_PIO
#define TX_BTN PA6_PIO
#define RX_BTN PA18_PIO
#define BATTERY_VOLTAGE_ADC ADC_CHANNEL_4

static adc_t battery_sensor;

static int battery_sensor_init (void)
{
    adc_cfg_t bat =
        {
            .channel = BATTERY_VOLTAGE_ADC,
            .bits = 12,
            .trigger = ADC_TRIGGER_SW,
            .clock_speed_kHz = F_CPU / 4000,
        };

    battery_sensor = adc_init (&bat);

    return (battery_sensor == 0) ? -1 : 0;
}

static uint16_t battery_millivolts (void)
{
    adc_sample_t s;

    adc_read (battery_sensor, &s, sizeof (s));

    // 33k pull down & 47k pull up gives a scale factor or
    // 33 / (47 + 33) = 0.4125
    // 4096 (max ADC reading) * 0.4125 ~= 1690
    return (uint16_t) ((int)s) * 3300 / 1690;
}

int main (void)
{
    spi_cfg_t spi_cfg =
        {
            .channel = 0,
            .clock_speed_kHz = 1000,
            .cs = RADIO_CS_PIO,
            .mode = SPI_MODE_0,
            .cs_mode = SPI_CS_MODE_FRAME,
            .bits = 8
        };
    nrf24_cfg_t nrf24_cfg =
        {
            .channel = RADIO_CHANNEL,
            .address = RADIO_ADDRESS,
            .payload_size = RADIO_PAYLOAD_SIZE,
            .ce_pio = RADIO_CE_PIO,
            .irq_pio = RADIO_IRQ_PIO,
            .spi = spi_cfg,
        };
    nrf24_t *nrf;
    uint8_t tx_count = 0;
    bool listening = false;

    /* Configure LED PIO as output.  */
    pio_config_set (TX_LED, PIO_OUTPUT_LOW);
    pio_config_set (RX_LED, PIO_OUTPUT_LOW);
    pacer_init (100);

    // Create non-blocking tty device for USB CDC connection.
    usb_serial_stdio_init ();

    // Start up the radio subsystem
#ifdef RADIO_POWER_ENABLE_PIO
    pio_config_set (RADIO_POWER_ENABLE_PIO, PIO_OUTPUT_HIGH);
    delay_ms (10);
#endif

    nrf = nrf24_init (&nrf24_cfg);
    if (! nrf)
        panic (LED_ERROR_PIO, 2);

    if (battery_sensor_init () < 0)
        panic (LED_ERROR_PIO, 3);

    // Set up the buttons
    button_cfg_t tx_cfg = {.pio = TX_BTN};
    button_cfg_t rx_cfg = {.pio = RX_BTN};

    button_t tx_btn = button_init (&tx_cfg);
    button_t rx_btn = button_init (&rx_cfg);
    if (!tx_btn)
        panic (LED_ERROR_PIO, 4);
    if (!rx_btn)
        panic (LED_ERROR_PIO, 5);

#if 0 // LED/switch tester for confirming hardware is okay
    while (1)
    {
        pio_output_set (TX_LED, pio_input_get (TX_BTN));
        pio_output_set (RX_LED, pio_input_get (RX_BTN));
        printf ("poll rx: %d tx: %d\n", button_poll (rx_btn), button_poll (tx_btn));
    }
#endif

    while (1)
    {
        char buffer[RADIO_PAYLOAD_SIZE];

        pacer_wait ();

        // If the tx button is pushed, stop listening & tx a packet
        // LED will turn on while transmitting, and off when done
        if (button_poll (tx_btn) == BUTTON_STATE_DOWN)
        {
            if (listening)
            {
                nrf24_power_down (nrf);
                pio_output_set (RX_LED, 0);
                listening = false;
            }
            pio_output_set (TX_LED, 1);
            sprintf (buffer, "Hello world %d", tx_count++);

            if (! nrf24_write (nrf, buffer, sizeof (buffer)))
            {
                printf ("TX: FAILURE\n");
            } else
            {
                printf ("TX: %s\n", buffer);
            }
        } else
        {
            pio_output_set (TX_LED, 0);
        }

        // If we're listening, and there is data available, then
        // pulse the LED low and print the data to the usb port
        if (listening)
        {
            if (nrf24_read (nrf, buffer, sizeof (buffer)))
            {
                pio_output_set (RX_LED, 0);
                printf ("RX: %s\n", buffer);
                pio_output_set (LED_STATUS_PIO, 0);
            }
            else
            {
                pio_output_set (RX_LED, 1);
            }
        }

        // If we press the rx button and we're not currently listening,
        // then start listening & turn the 'receiving' led on
        if (button_poll (rx_btn) == BUTTON_STATE_DOWN && !listening)
        {
            if (!nrf24_listen (nrf))
                panic (LED_ERROR_PIO, 6);
            pio_output_set (RX_LED, 1);
            listening = true;
        }

        // Flash the lights if we ever go to low battery state
        while (battery_millivolts () < 5000)
        {
            pio_output_toggle (TX_LED);
            delay_ms (200);
        }
    }
}
