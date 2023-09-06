/**
 * @file radio_sm_hat.h
 * @author Jamie Thomas
 * @brief 
 * @date 2023-05-17
 */

#ifndef RADIO_SM_HAT_H
#define RADIO_SM_HAT_H

#include "adxl_data.h"
#include "pio.h" //For led responses to radio sending
#include "radio_hat.h"
#include "usb_serial.h" // TESTING
#include "buzzer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void radio_state_machine(void);


#endif /* RADIO_SM_HAT_H */