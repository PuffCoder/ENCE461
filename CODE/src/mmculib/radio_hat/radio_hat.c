/**
 * @file radio_hat.c
 * @author Jamie Thomas
 * @brief Runs radio functions
 * @date 2023-05-17
 */

#include "radio_hat.h"




/*
 * Test function that should send "Hello world" from the radio. 
 */
bool
send_hello_world(void)
{

    radio_message_t message = { .message_type = RADIO_TEST };

    snprintf (message.buffer, sizeof (message.buffer), "Hello world, test file\r\n");

    return radio_send(message);
}


/*
 * Sends left and right motor instructions through the radio. 
 */
bool 
send_motor_instructions(motor_speed_t motor_instructions)
{
    radio_message_t message = { .message_type = RADIO_MOTOR };

    snprintf (message.buffer, sizeof (message.buffer), "%+d,%+d\r\n", motor_instructions.left, motor_instructions.right);

    return radio_send(message);
}


bool 
get_radio_response(radio_message_t *message)
{
    return radio_get(message);
}






