/** @file   adxl_data.h
    @author Jamie Thomas
    @date   11 May 2023
    @brief  The ADXL345 accelerometer chip data formatting to motor values. 
*/

#ifndef ADXL_DATA_H
#define ADXL_DATA_H

#include "config.h"
#include "target.h"
#include "pio.h"
#include "adxl345.h"
#include "circ_buff.h"

typedef struct {
    int16_t left;
    int16_t right;
} motor_speed_t;

void
get_motor_speeds (int16_t accel[3], motor_speed_t *motor_speed);

void
get_accel_data (int16_t accel[3]);

void
poll_accel (void);

bool
accel_init (void);

void accel_deinit(void);

#endif /* ADXL_DATA_H */
