/** @file led.h
    @author Heng Yin
    @date 14 May 2023
    @brief LED component
    @note 
*/

#ifndef CARLED_H
#define CARLED_H

#include <pio.h>
#include "target.h"
#include "pacer.h"
#include "led.h"


void LED_TurnOff(led_t led);
void LED_TurnOn(led_t led);

#endif
