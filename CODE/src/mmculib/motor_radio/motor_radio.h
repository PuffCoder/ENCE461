/** @file   motor_radio.h
    @author Heng Yin, John Elliott
    @date   18 May 2023
    @brief  Radio controls for the racer
*/

#ifndef MOTOR_RADIO_H
#define MOTOR_RADIO_H

#include "config.h"
#include "pio.h"
#include "radio_freq.h"
#include "delay.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct motor_speed_t {
  int16_t left_s;
  int16_t right_s;
} motor_speed_t;

bool radio_tx_run(int16_t);

bool radio_rx_run(motor_speed_t*);

#ifdef __cplusplus
}
#endif
#endif

