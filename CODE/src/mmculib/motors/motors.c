/* File:   motors.c
   Author: Heng Yin, John Elliott
   Date:   16 May 2023
   Descr:  This code sets up and runs the motors.
*/
#include "motors.h"


circBuf_t left_data;
circBuf_t right_data;
pwms_t pwms;

// Setup the PWMS and Buffers
void motor_init(void) {
  initCircBuf (&left_data, BUF_SIZE);
  initCircBuf (&right_data, BUF_SIZE);

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

  // Motor init
  pwms.pwm1 = pwm_init(&pwm1_cfg);
  pwms.pwm2 = pwm_init(&pwm2_cfg);
  pwms.pwm3 = pwm_init(&pwm3_cfg);
  pwms.pwm4 = pwm_init(&pwm4_cfg);
}


/*
Used to turn on motors. As each motor has 2 PWM signals when starting a PWM signal the alternative signal is first turned off.
This stops the motors from "trying to spin both ways". 

To turn off a motor completly the speed should be set to 0.
*/ 
void pwm_change(pwm_t pwm_on, pwm_t pwm_off, int16_t speed)
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

Speed is a percentage of the duty cycle. Speeds below 8% often dont work.
*/
bool motor_control(uint8_t m_pick, int16_t raw_speed)
{
  int16_t speed = (((double) abs(raw_speed)) / 256.0) * 100;
  if (m_pick == LEFT_MOTOR) { // Pick left motor
      if ((raw_speed < 0) == false) { // Left
        pwm_change(pwms.pwm2, pwms.pwm1, speed);
      } else { // Right
        pwm_change(pwms.pwm1, pwms.pwm2, speed);
      }
  } else if (m_pick == RIGHT_MOTOR) { // Pick right motor
      if ((raw_speed < 0) == false) { // Left
        pwm_change(pwms.pwm4, pwms.pwm3, speed);
      } else { // Right
        pwm_change(pwms.pwm3, pwms.pwm4, speed);
      }
  } else {
        return false;
  }
  return true;
}

/*
Used by the state machine to update the motors.
*/
void update_motors(motor_speed_t racer) {
  writeCircBuf(&left_data, racer.left_s);
  writeCircBuf(&right_data, racer.right_s);
            
  // Update motors and check if error occured.
  motor_control (LEFT_MOTOR, readAverageCircBuf(&left_data));
  motor_control (RIGHT_MOTOR, readAverageCircBuf(&right_data));
}

void stop_motors() {
  motor_control(LEFT_MOTOR, 0);
  motor_control(RIGHT_MOTOR, 0);
}

void start_motors() {
    // Update motors and check if error occured.
  motor_control (LEFT_MOTOR, readAverageCircBuf(&left_data));
  motor_control (RIGHT_MOTOR, readAverageCircBuf(&right_data));
}