/**
 * @file battery_monitor.c
 * @author Heng Yin
 * @brief battery monitor 
 * @date 2023-05-22
 */

#ifndef BATTERY_MONITOR_H 
#define BATTERY_MONITOR_H 

#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "adc.h"
#include "pio.h"
#include "usb_serial.h"
#include "pacer.h"
#include "panic.h"
#include "circ_buff.h"



bool battery_monitor_init(void);

/* void adc_send(void); */
/* uint16_t adc_send(void); */
// double adc_send(void);
void batt_States(void);


void poll_battery(void);

bool check_battery_ok(void);

#endif /* RADIO_FUNCT_H */
