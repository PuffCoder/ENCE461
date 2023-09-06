/**
 * @file radio_funct.c
 * @author Jamie Thomas, John Elliott
 * @brief Runs radio functions
 * @date 2023-05-16
 */

#include <stdlib.h>
#include <string.h>
#include "radio_funct.h"


static nrf24_t *nrf;

bool
radio_init(void)
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

    init_radio_switches (&nrf24_cfg);

    // Check radio channel choice
    bool check = check_radio_switches(&nrf24_cfg);
    if (check)
    {
        pio_output_set(LED_STATUS_PIO, 1);
    }
    else
    {
        pio_output_set(LED_STATUS_PIO, 0);
    }

    // Enable radio regulator if present.
    pio_config_set (RADIO_POWER_ENABLE_PIO, PIO_OUTPUT_HIGH);
    delay_ms (10);

    nrf = nrf24_init (&nrf24_cfg);
    return !(! nrf); 
}

void radio_turn_off(void)
{

    nrf24_power_down (nrf);

}

void radio_turn_on(void)
{

    nrf24_power_up (nrf);
    
}


/*
 * Converts and writes a radio_message_t to a buffer, with its message type at the start, followed by 4 '0's (Can be changed). 
 */
static void
message_to_buffer(char buffer[RADIO_PAYLOAD_SIZE + 1], radio_message_t *message)
{
    snprintf (buffer, RADIO_PAYLOAD_SIZE + 1 , "%d,%s", message->message_type, message->buffer);
}


/*
 * Sends the message stored in the global buffer. Adds the message type to the start of the message before sending the buffer. 
 */
bool
radio_send(radio_message_t message)
{
    // Message is a struct with a buffer and an enum type of message type. The type should be added to the start of the buffer before being sent. 
    char buffer[RADIO_PAYLOAD_SIZE + 1];
    
    message_to_buffer(buffer, &message);
    // Some code to add type to buffer. 

    return nrf24_write (nrf, buffer, RADIO_PAYLOAD_SIZE);
}

/*
    Gets a message and stores it in a message structure. Splits the incoming message into message type and message info. 
*/
bool
radio_get(radio_message_t* message)
{
    char buffer[RADIO_PAYLOAD_SIZE + 1];
    uint8_t bytes = nrf24_read (nrf, buffer, RADIO_PAYLOAD_SIZE);
    if (bytes != 0) {
        const char s[2] = ",";
        char* msg_type = strtok(buffer, s); // Gets message type
        snprintf(message->buffer, sizeof(message->buffer), "%s\r\n", strtok(NULL, "")); // Gets rest of string (message info).
        message->message_type = atoi(msg_type);
        return 1;
    }
    return 0;
}




