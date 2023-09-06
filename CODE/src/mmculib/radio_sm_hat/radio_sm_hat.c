/**
 * @file radio_sm.c
 * @author Jamie Thomas
 * @brief
 * @date 2023-05-17
 */

#include "radio_sm_hat.h"

typedef enum
{

    SENDING_STATE,
    RECEIVING_STATE,

} radio_state_t;

#ifndef LED_ACTIVE
#define LED_ACTIVE 0
#endif

#define ATTEMPTS 10

static void sending_state_driver(radio_state_t *radio_state);
static void receiving_state_driver(radio_state_t *radio_state);

/**
 * Hat radio state machine.
 * Switches between sending and receiving on the radio and runs the relevant functions.
 */
void radio_state_machine(void)
{

    static radio_state_t radio_state = SENDING_STATE;

    switch (radio_state)
    {

    case SENDING_STATE:
    {

        sending_state_driver(&radio_state);
        break;
    }
    case RECEIVING_STATE:
    {

        receiving_state_driver(&radio_state);
        break;
    }
    default:
    {

        radio_state = SENDING_STATE;
        break;
    }
    }
}

/**
 * Sends motor data to racer.
 *  Operations:
 *      - Poll accelerometer to update modules data (Could be shifted to main to have quicker polling times).
 *      - Read accelerometer from module to (x, y, z) format.
 *      - Translate accelerometer data to motor speeds (left, right).
 *      - Send motor speeds to racer over radio.
 *          - if this succeeds, turn off error LED and set SM to receiving state.
 *          - else turn on error LED.
 */
void sending_state_driver(radio_state_t *radio_state)
{
    static int attempt_count = 0;

    static motor_speed_t motor_speed = {0, 0};

    // Get accelerometer data
    int16_t accel[3];
    get_accel_data(accel);
    get_motor_speeds(accel, &motor_speed);

    // Send the accelerometer data
    if (send_motor_instructions(motor_speed)) // If succeeds to send
    {
        pio_output_set(LED_ERROR_PIO, !LED_ACTIVE);
        // change state, as message sent successfully
        attempt_count = 0;
        *radio_state = RECEIVING_STATE;
    }
    else
    {
        pio_output_set(LED_ERROR_PIO, LED_ACTIVE);
    }

    // For testing values that are sent to racer
    printf("   x: %5d      y: %5d  z: %5d\n", accel[0], accel[1], accel[2]); // TESTING
    printf("left: %5d  right: %5d\n", motor_speed.left, motor_speed.right);  // TESTING

    attempt_count++;
    if (attempt_count > ATTEMPTS)
    {
        printf("Too many attempts sending, switching to recieving state. \n");
        attempt_count = 0;
        *radio_state = RECEIVING_STATE;
    }
}

/**
 * Receives messages from racer over radio.
 * Operations if...:
 *      Bumper hit:
 *       - Turn on buzzer.
 */
void receiving_state_driver(radio_state_t *radio_state)
{

    static int attempt_count = 0;

    radio_message_t message;
    bool message_received = get_radio_response(&message);

    if (message_received)
    {
        pio_output_set(LED_STATUS_PIO, LED_ACTIVE);
        *radio_state = SENDING_STATE;
        attempt_count = 0;
        int16_t message_value;
        switch (message.message_type)
        {
        case RADIO_BUMPER:
            message_value = (int16_t)atoi(message.buffer);
            if (message_value == 1)
            {
                pio_output_set(LED_STATUS_PIO, LED_ACTIVE);
                run_buzzer();
                pio_output_set(LED_STATUS_PIO, !LED_ACTIVE);
            }
            else
            {
                // printf("Bumper Message Received: %s\n", message.buffer);
            }
            break;
        case RADIO_TEST:
            printf("Test Message Received: %s\n", message.buffer);
            break;
        default:
            printf("Random Message Received: %s\n", message.buffer);
            break;
        }
    }
    else
    {
        pio_output_set(LED_STATUS_PIO, !LED_ACTIVE);
    }

    //*radio_state = SENDING_STATE; //Test code to make it switch back to send state every switch.

    attempt_count++;
    if (attempt_count > ATTEMPTS)
    {
        printf("Too many attempts receiving, switching to sending state. \n");
        attempt_count = 0;
        *radio_state = SENDING_STATE;
    }
}
