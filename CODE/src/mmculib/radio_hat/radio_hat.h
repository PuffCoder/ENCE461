/**
 * @file radio_hat.h
 * @author Jamie Thomas
 * @brief Runs radio functions
 * @date 2023-05-17
 */

#ifndef RADIO_HAT_H
#define RADIO_HAT_H

#include "config.h"
#include "pio.h"
#include "nrf24.h"
#include "radio_freq.h"
#include "adxl_data.h"
#include "radio_funct.h"



bool send_hello_world(void);

bool send_motor_instructions(motor_speed_t motor_instructions);

bool get_radio_response(radio_message_t *message);

#endif /* RADIO_HAT_H */