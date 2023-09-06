/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   12 February 2018
    @brief
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* This is for the carhat (chart) board configured as a racer!  */

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
#define USB_VBUS_PIO PB13_PIO
#define USB_CURRENT_MA 500

/* SW 1,2 - nRST & ERASE */
// #define nRST NRST // 39
// #define ERASE PB12_PIO

/* LEDs  */
#define LED_ERROR_PIO PB14_PIO
#define LED_STATUS_PIO PA31_PIO

/* 8 PIN Header */
#define EXpin5 PB3_PIO
#define EXpin6 PB2_PIO
#define EXpin7 PA16_PIO
#define EXpin8 PB1_PIO

/* General  */
// #define APPENDAGE_PIO PA1_PIO
// #define SERVO_PWM_PIO PA2_PIO

/* Button  */
#define BUTTON_PIO4 PB4_PIO // SW 4

/* Radio  */
#define RADIO_CS_PIO PA11_PIO
#define RADIO_CE_PIO PA10_PIO
#define RADIO_IRQ_PIO PA20_PIO
// have not used
// #define RADIO_MOSI_PIO PA13_PIO
// #define RADIO_MISO_PIO PA12_PIO
// #define RADIO_SCK_PIO PA14_PIO
//
/* Radio Switches */
#define SWITCH_1 PA23_PIO
#define SWITCH_2 PA22_PIO
#define SWITCH_3 PA27_PIO
#define SWITCH_4 PA19_PIO
#define SWITCH_PULL_DIRECTION PIO_PULLUP

/* BUFFER SIZE */
#define BUF_SIZE 5

// --------- TO DO LIST ---------

/* Battary ADC */
#define BATTERY_ADC_CHANNEL ADC_CHANNEL_8
#define BATTERY_ADC_LIMIT 41

/* Bump Sensor */
#define BUMP_PIO PB0_PIO

/* LED tape  */
#define LEDTAPE_PIO PB5_PIO

/* SLEEP */
#define BUTTON_SLEEP PA8_PIO

/* Regulation ENABLE */
#define RADIO_POWER_ENABLE_PIO PA9_PIO

/* H-bridges   */
// #define MOTOR_LEFT_PWM_PIO PA11_PIO
#define MOTOR_RIGHT_PWM_PIO PA7_PIO
#define H_BRIDGE_SLEEP PA6_PIO  // SW 3

// Interrupt
#define ID_IRQ0 11

#endif /* TARGET_H  */
