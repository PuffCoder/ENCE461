/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   12 February 2018
    @brief
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* This is for the carhat (chart) board configured as a hat!  */

/* System clocks  */
#define F_XTAL 12.00e6
#define MCU_PLL_MUL 16
#define MCU_PLL_DIV 1

#define MCU_USB_DIV 2
/* 192 MHz  */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 96 MHz  */
#define F_CPU (F_PLL / 2)

/* TWI  */
#define TWI_TIMEOUT_US_DEFAULT 10000
#define MPU_ADDRESS 0x68

/* USB  */
#define USB_VBUS_PIO PA19_PIO
#define USB_CURRENT_MA 500

/* ADC  */
#define BATTERY_ADC_CHANNEL ADC_CHANNEL_4
#define BATTERY_ADC_LIMIT 50
// #define JOYSTICK_X_ADC_CHANNEL ADC_CHANNEL_6
// #define JOYSTICK_Y_ADC_CHANNEL ADC_CHANNEL_5

/* IMU  */
// #define IMU_INT_PIO PA0_PIO

/* LEDs  */
#define LED_ERROR_PIO PA0_PIO
#define LED_STATUS_PIO PA1_PIO

/* General  */
// #define APPENDAGE_PIO PA1_PIO
// #define SERVO_PWM_PIO PA2_PIO
#define BUZZER_PIO PB5_PIO

/* Button  */
#define BUTTON_PIO PA16_PIO
#define BUTTON_2_PIO PA15_PIO
#define BUTTON_SLEEP PA8_PIO

/* Spare Headers */
#define HEADER_1_PIO PB1_PIO
#define HEADER_2_PIO PB14_PIO
#define HEADER_3_PIO PB13_PIO
#define HEADER_4_PIO PA31_PIO

/* Radio Switches */
#define SWITCH_1 PA18_PIO
#define SWITCH_2 PA21_PIO
#define SWITCH_3 PA22_PIO
#define SWITCH_4 PA23_PIO
#define SWITCH_PULL_DIRECTION PIO_PULLDOWN

/* Radio  */
#define RADIO_CS_PIO PA11_PIO
#define RADIO_CE_PIO PA10_PIO
#define RADIO_IRQ_PIO PA25_PIO
#define RADIO_POWER_ENABLE_PIO PA9_PIO

/* LED tape  */
#define LEDTAPE_PIO PA2_PIO

/* Accelerometer */
#define ADXL345_ADDRESS 0x53
#define ACCEL_CS PA27_PIO // Not sure if this is useful
#define ACCEL_INT_1 PA29_PIO
#define ACCEL_INT_2 PA28_PIO

#define BUF_SIZE 10

// Interrupt
#define ID_IRQ0 11

#endif /* TARGET_H  */
