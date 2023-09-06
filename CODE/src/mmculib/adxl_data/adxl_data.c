/** @file   adxl_data.c
    @author Jamie Thomas
    @date   11 May 2023
    @brief  The ADXL345 accelerometer chip data formatting to motor values. 
*/


#include "adxl_data.h"


static twi_t adxl345_twi;
static adxl345_t *adxl345;

static circBuf_t accl_buffer_x;
static circBuf_t accl_buffer_y;
static circBuf_t accl_buffer_z;


bool
accel_init (void)
{

    static twi_cfg_t adxl345_twi_cfg =
    {
        .channel = TWI_CHANNEL_0,
        .period = TWI_PERIOD_DIVISOR (100000), // 100 kHz
        .slave_addr = 0
    };

    // Initialise the TWI (I2C) bus for the ADXL345
    adxl345_twi = twi_init (&adxl345_twi_cfg);

    // Initialise the ADXL345
    adxl345 = adxl345_init (adxl345_twi, ADXL345_ADDRESS);

    initCircBuf (&accl_buffer_x, BUF_SIZE);
    initCircBuf (&accl_buffer_y, BUF_SIZE);
    initCircBuf (&accl_buffer_z, BUF_SIZE);

    return (! (! adxl345) && ! (! adxl345_twi));

}

void accel_deinit(void) 
{

    twi_shutdown(adxl345_twi);
    

}


/*
 * Takes accelerometer data and returns motor speeds based on their data. 
 * Current setup: 
 *      The top of the board is considered the front, and lowering the front goes forward. 
 *      Y: forward and backward
 *      X: left and right
 * 
 * @param accel 'accel' should always be a 3 item long list. 
 */
void
get_motor_speeds (int16_t accel[3], motor_speed_t *motor_speed)
{
    // TODO Needs some magic to turn x, y and z into motor values (between -265 and 265?)
    int16_t x = accel[0];
    int16_t y = accel[1];
    int16_t left = 0;
    int16_t right = 0;

    // Motors dont seem to move until 200

    if (y > 25)
    {
        left += ((y) * 2.5);
        right += ((y) * 2.5);
    }
    else if (y < -25)
    {
        left += ((y) * 2.5);
        right += ((y) * 2.5);
    }

    if (left > 256)
        left = 256;
    if (left < -256)
        left = -256;
    if (right > 256)
        right = 256;
    if (right < -256)
        right = -256;
    
    if (x > 25) // Trun Right
    {
        if (right > 0) {
            if (right > 230) {
                right += -((x) * 1) / 2;
            } else {
                right += -(((x) * 7) / 10);
            }
        } else {
            if (right < -230) {
                right += ((x) * 1) / 2;
            } else {
                right += (((x) * 7) / 10);
            }
        }
        
    }
    else if (x < -25)
    {
        if (left > 0) {
            if (left > 230) {
                left += ((x) * 1) / 2;
            } else {
                left += (((x) * 7) / 10);
            }
        } else {
            if (left < -230) {
                left += -((x) * 1) / 2;
            } else {
                left += -(((x) * 7) / 10);
            }
        }
        
        
    }

    if (left > 256)
        left = 256;
    if (left < -256)
        left = -256;
    if (right > 256)
        right = 256;
    if (right < -256)
        right = -256;

    motor_speed->left = left;
    motor_speed->right = right;
}


/**
 * Read buffers (average) and return through accel input. (Then something will run get_motor_speeds on this data. )
 */
void
get_accel_data (int16_t accel[3])
{
    accel[0] = readAverageCircBuf (&accl_buffer_x);
    accel[1] = readAverageCircBuf (&accl_buffer_y);
    accel[2] = readAverageCircBuf (&accl_buffer_z);
}


/**
 * Poll the accelerometer and write the data to the circular buffers. 
 */
void
poll_accel (void)
{
    
    int16_t accel[3];
    if (adxl345_is_ready (adxl345))
    {
        adxl345_accel_read (adxl345, accel);
        writeCircBuf (&accl_buffer_x, (accel[0]));
        writeCircBuf (&accl_buffer_y, (accel[1]));
        writeCircBuf (&accl_buffer_z, (accel[2]));
    }

}

