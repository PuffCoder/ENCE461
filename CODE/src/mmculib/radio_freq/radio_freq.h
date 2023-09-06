/**
 * @file radio_freq.h
 * @author Jamie Thomas
 * @brief Checks for radio switches (1 and 2) to check which channel to run the radio on. 
 * @date 2023-05-09
 */

#ifndef RADIO_FREQ_H
#define RADIO_FREQ_H

#include "config.h"
#include "pio.h"
#include "button.h"
#include "nrf24.h"

// nrf24 initialize
#define RADIO_CHANNEL 5
#define RADIO_ADDRESS 0x0123456789LL
#define RADIO_PAYLOAD_SIZE 32

#define BUTTON_POLL_RATE 100

// RADIO CHANNELS
#define NUMBER_OF_CHANNELS 4  // Update with new values added below. Is used as if it is the length of the below list. 
static const int radio_channels[NUMBER_OF_CHANNELS] = {5, 38, 52, 103};  // Possible channels
#define NUMBER_OF_SWITCH_BITS 2  // Number of switches used to count in binary. 

typedef struct
{
    bool switch_1;
    bool switch_2;
    bool switch_3;
    bool switch_4;
} switch_radio_state_t;


void
init_radio_switches(nrf24_cfg_t *nrf24_cfg);

bool
check_radio_switches(nrf24_cfg_t *nrf24_cfg);


#endif /* RADIO_FREQ_H */
