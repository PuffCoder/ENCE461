/* File:   motors.c
   Author: Heng Yin, John Elliott
   Date:   16 May 2023
   Descr:  This code sets up and runs the motors.
*/
#include "pwm.h"
#include "motors.h"
#include "pio.h"
#include "panic.h"


// PWM Setups
static const pwm_cfg_t pwm1_cfg =
{
    .pio = PWM1_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};
static const pwm_cfg_t pwm2_cfg =
{
    .pio = PWM2_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};
static const pwm_cfg_t pwm3_cfg =
{
    .pio = PWM3_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};
static const pwm_cfg_t pwm4_cfg =
{
    .pio = PWM4_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 50),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};

/*
Used to turn on motors. As each motor has 2 PWM signals when starting a PWM signal the alternative signal is first turned off.
This stops the motors from "trying to spin both ways". 

To turn off a motor completly the speed should be set to 0.
*/ 
void pwm_change(pwm_t pwm_on, pwm_t pwm_off, uint8_t speed)
{
    pwm_stop(pwm_off); 
    if (speed != 0) {
        pwm_duty_set(pwm_on, PWM_DUTY_DIVISOR(PWM_FREQ_HZ, speed));
        pwm_start(pwm_on); 
    } else {
        pwm_stop(pwm_on); 
    }
}

/*
Picks a motor via m_pick (0=left, 1=right) then a direction m_direction (0=left, 1=right).
If an invalid value is used panic for the ERROR LED is triggered. Else the speed value is set for the corisponding motor.

Most speeds below 80 will not trigger the motors to spin.
*/
void motor_control(int m_pick, int m_direction, int speed, pwm_t pwm1, pwm_t pwm2, pwm_t pwm3, pwm_t pwm4)
{
  if (m_pick == 0) { // Pick left motor
      if (m_direction == 0) { // Left
        pwm_change(pwm2, pwm1, speed);
      } else if (m_direction == 1) { // Right
        pwm_change(pwm1, pwm2, speed);
      }
  } else if (m_pick == 1) { // Pick right motor
      if (m_direction == 0) { // Left
        pwm_change(pwm4, pwm3, speed);
      } else if (m_direction == 1) { // Right
        pwm_change(pwm3, pwm4, speed);
      }
  }
}