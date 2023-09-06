/** @file   motors.h
    @author Heng Yin, John Elliott
    @date   16 May 2023
    @brief  Motor controls 
*/

#ifndef MOTORS_H
#define MOTORS_H

#include <stdlib.h>
#include "pwm.h"
#include "pio.h"
#include "panic.h"
#include "circ_buff.h"
#include "motor_radio.h"

#ifdef __cplusplus
extern "C" {
#endif

// PWMS
#define PWM1_PIO PA17_PIO
#define PWM2_PIO PA2_PIO
#define PWM3_PIO PA1_PIO
#define PWM4_PIO PA0_PIO
#define PWM_FREQ_HZ 100e3
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

typedef struct pwms_t {
  pwm_t pwm1;
  pwm_t pwm2;
  pwm_t pwm3;
  pwm_t pwm4;
} pwms_t;

void motor_init(void);

void pwm_change(pwm_t, pwm_t, int16_t);

bool motor_control(uint8_t, int16_t);

void update_motors(motor_speed_t);

void stop_motors(void);

void start_motors(void);


#ifdef __cplusplus
}
#endif
#endif
