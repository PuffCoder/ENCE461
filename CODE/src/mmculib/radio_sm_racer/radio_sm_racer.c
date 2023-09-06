#include "radio_sm_racer.h"
#include "motors.h"
#include "motor_radio.h"
#include "bumper.h"
#include "pio.h"
#include "ledstrip.h"

typedef enum {
    SENDING_STATE,
    RECEIVING_STATE,
} radio_state_t;

static bool pressed = false;

static void sending_state_driver(radio_state_t* radio_state);
static void recieving_state_driver(radio_state_t* radio_state);



void radio_state_machine(void)
{

    static radio_state_t radio_state = RECEIVING_STATE;

    switch (radio_state) {

        case SENDING_STATE:
        {

            sending_state_driver(&radio_state);
            break;

        }
        case RECEIVING_STATE:
        {

            recieving_state_driver(&radio_state);
            break;

        }
        default :
        {

            radio_state = SENDING_STATE;
            break;

        }

    }

}


void sending_state_driver(radio_state_t* radio_state)
{
    if (!pressed) {
        pressed = update_bumper();
    }

    if (radio_tx_run(pressed)) {
        if (pressed) {
            stop_motors();
        } else {
            start_motors();
        }
        *radio_state = RECEIVING_STATE;
        
    }
    
    
    set_bumper(pressed);
}


void recieving_state_driver(radio_state_t* radio_state)
{
    motor_speed_t racer_s;           // motor speed type value 
    if (radio_rx_run(&racer_s)) { 
        update_motors(racer_s);     // motor speed be updated
        *radio_state = SENDING_STATE;
        if (pressed) {
            rainbow_init();
        }
        pressed = false; 
    }
}
