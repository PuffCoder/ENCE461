/**
 * @file buzzer.h
 * @author Jamie Thomas
 * @brief 
 * @date 2023-05-18
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "config.h"
#include "delay.h"
#include "pwm.h"
#include "music.h"

#define PWM_FREQ_HZ 5e3









void
buzzer_init(void);

void
run_buzzer(void);

void
run_buzzer_extended(void);

void
sleep_buzzer (void);


#endif /* BUZZER_H */