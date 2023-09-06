/**
 * @file radio_funct.h
 * @author Jamie Thomas
 * @brief Runs radio functions
 * @date 2023-05-16
 */

#ifndef RADIO_FUNCT_H
#define RADIO_FUNCT_H

#include "config.h"
#include "pio.h"
#include "nrf24.h"
#include "radio_freq.h"
#include "delay.h"


typedef enum radio_message_enum 
{
    RADIO_TEST = 1,          /* Test messages of some sort.  */
    RADIO_MOTOR,             /* Motor instructions message.  */
    RADIO_BUMPER             /* Bumper instructions message. */ 
} radio_message_type_t;


typedef struct 
{
    char buffer[RADIO_PAYLOAD_SIZE - 5];
    radio_message_type_t message_type;
} radio_message_t;


bool radio_init(void);

void radio_turn_off(void);

void radio_turn_on(void);

bool radio_send(radio_message_t message);

bool radio_get(radio_message_t* message);

static void message_to_buffer(char buffer[RADIO_PAYLOAD_SIZE + 1], radio_message_t *message);

#endif /* RADIO_FUNCT_H */