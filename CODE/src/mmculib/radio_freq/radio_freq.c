/**
 * @file radio_freq.c
 * @author Jamie Thomas
 * @brief Checks for radio switches (1 and 2) to check which channel to run the radio on. 
 * @date 2023-05-09
 */

#include "radio_freq.h"


static switch_radio_state_t switch_radio_state = 
{
    .switch_1 = false,
    .switch_2 = false,
    .switch_3 = false,
    .switch_4 = false,
};

/*
 * Get the 'i'th last switch state, On (true) or off (false). 
 */
static bool
get_switch_state(switch_radio_state_t* switches, int i)
{
    switch (i)
    {
        case 1: return switches->switch_1;
        case 2: return switches->switch_2;
        case 3: return switches->switch_3;
        case 4: return switches->switch_4;
        default: return switches->switch_4;
    }
}

/*
 * Set the 'i'th switch state to boolean, On (true) or off (false). 
 */
static void 
set_switch_state(switch_radio_state_t* switches, int i, bool state)
{
    switch (i)
    {
        case 1: 
            switches->switch_1 = state;
            break;
        case 2: 
            switches->switch_2 = state;
            break;
        case 3: 
            switches->switch_3 = state;
            break;
        case 4: 
            switches->switch_4 = state;
            break;
    }
}

/*
 * Get the 'i'th switch pio definition. 
 */
static pio_t
get_switch_pio(int i)
{
    switch (i)
    {
        case 1: return SWITCH_1;
        case 2: return SWITCH_2;
        case 3: return SWITCH_3;
        case 4: return SWITCH_4;
        default: return SWITCH_4;
    }
}

/*
 * Initialises switches and applies the correct radio channel to the config. 
 * NEEDS TO BE RUN BEFORE "nrf24_init", or one of these methods must run the other. 
 */
void
init_radio_switches(nrf24_cfg_t *nrf24_cfg)
{
    for (int i = 1; i <= NUMBER_OF_SWITCH_BITS; i++) 
    {
        pio_config_set (get_switch_pio(i), SWITCH_PULL_DIRECTION);
        // set_switch_state(&switch_radio_state, i, pio_input_get (get_switch_pio(i)));
    }
}

/*
 * Change the radio channel. Get the switches and find the right channel to change it to. 
 */
static void
update_radio_channel(nrf24_cfg_t *nrf24_cfg)
{
    int channel_choice = 0;
    for (int i = 0; i < NUMBER_OF_SWITCH_BITS; i++)
    {
        channel_choice += get_switch_state(&switch_radio_state, i + 1) << i;
    }

    if (channel_choice >= NUMBER_OF_CHANNELS)
    {
        channel_choice = NUMBER_OF_CHANNELS - 1;
    }

    nrf24_cfg->channel = radio_channels[channel_choice];
}

/*
 * Returns true if the switches have changed, false otherwise. If the switches have changed, 
 * change the urf24_cfg radio channel to the new channel. 
 */
bool
check_radio_switches(nrf24_cfg_t *nrf24_cfg)
{

    // Idea: Check if the switch states have changed. If so, set corrisponding channel on input (nrf24_cfg)
    //       and then return true to make the main file re-initialise the radio with the new channel. 

    bool something_changed = false;

    for (int i = 1; i <= NUMBER_OF_SWITCH_BITS; i++)
    {
        bool old_state = get_switch_state(&switch_radio_state, i);
        bool new_state;
        switch (SWITCH_PULL_DIRECTION)
        {
            case PIO_PULLDOWN:
                new_state = pio_input_get (get_switch_pio(i));
                break;
            case PIO_PULLUP:
                new_state = ! pio_input_get (get_switch_pio(i));
                break;
            default:
                new_state = pio_input_get (get_switch_pio(i));
                break;
        }
        
        if (old_state != new_state)
        {
            
            something_changed = true;
            set_switch_state(&switch_radio_state, i, new_state);
        }
    }

    if (something_changed)
    {
        update_radio_channel(nrf24_cfg);
    }

    return something_changed;

}





