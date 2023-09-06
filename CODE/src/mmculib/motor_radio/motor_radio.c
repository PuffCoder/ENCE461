/* File:   motor_radio.c
   Author: Heng Yin, John Elliott
   Date:   18 May 2023
   Descr:  This code sets up racer radio system.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "motor_radio.h"
#include "radio_funct.h"

#ifndef LED_ACTIVE
#define LED_ACTIVE 0
#endif

/*
    Takes a radio message when the bumper is hit and sends it to the hat.
*/
bool radio_tx_run(int16_t bumper_mes)
{
        radio_message_t message = {
            .message_type = RADIO_BUMPER
        };
        snprintf(message.buffer, sizeof(message.buffer), "%d\r\n", bumper_mes);
        bool succesful = radio_send(message);
        if (succesful) {
            pio_output_set(LED_ERROR_PIO, LED_ACTIVE);
        } else {
            pio_output_set(LED_ERROR_PIO, !LED_ACTIVE);
        }
        return succesful;
}

/*
    Gets a radio input for the motor and returns the values.
*/
bool radio_rx_run(motor_speed_t* racer)
{
    radio_message_t message;
    // Gets radio message
    if (radio_get(&message)) {
        const char s[2] = ",";
        racer->left_s = atoi(strtok(message.buffer, s));  // Gets left value and converts it to an int.
        racer->right_s = atoi(strtok(NULL, s));           // Gets right value and converts it to an int.
        pio_output_set(LED_STATUS_PIO, LED_ACTIVE);
        return true;
    } else {
        pio_output_set(LED_STATUS_PIO, !LED_ACTIVE);
    }
    return false;
}







