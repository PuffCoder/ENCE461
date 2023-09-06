/** @file   motors.h
    @author Heng Yin, John Elliott
    @date   16 May 2023
    @brief  Motor controls 
*/

#ifndef MOTORS_H
#define MOTORS_H

#ifdef __cplusplus
extern "C" {
#endif

// PWMS
#define PWM1_PIO PA17_PIO
#define PWM2_PIO PA2_PIO
#define PWM3_PIO PA1_PIO
#define PWM4_PIO PA0_PIO
#define PWM_FREQ_HZ 100e3


void pwm_change(pwm_t pwm_on, pwm_t pwm_off, uint8_t speed);
void motor_control(int m_pick, int m_direction, int speed, pwm_t pwm1, pwm_t pwm2, pwm_t pwm3, pwm_t pwm4);


#ifdef __cplusplus
}
#endif
#endif
