/**
 * @file buzzer.c
 * @author Jamie Thomas
 * @brief
 * @date 2023-05-18
 */

#include "buzzer.h"

static pwm_t buzzer;

void buzzer_init(void)
{
	static const pwm_cfg_t pwm1_cfg =
		{
			.pio = BUZZER_PIO,
			.period = PWM_PERIOD_DIVISOR(PWM_FREQ_HZ),
			.duty = PWM_DUTY_DIVISOR(PWM_FREQ_HZ, 50),
			.align = PWM_ALIGN_LEFT,
			.polarity = PWM_POLARITY_HIGH,
			.stop_state = PIO_OUTPUT_LOW};
	buzzer = pwm_init(&pwm1_cfg);
}

/**
 * Plays a song that lasts 5 seconds.
 */
void run_buzzer(void)
{
	static int counter = 0;
	switch (counter)
	{
	case 0:
		play_star_wars(buzzer);
		break;
	case 1:
		play_star_wars_imperial_march(buzzer);
		break;
	case 2:
		// // Nice sounding, but not 5 seconds
		// music_set_playback_speed(1.5);
		// play_star_wars_cantina(buzzer);
		// music_set_playback_speed(1);

		// 5 second fast version (slightly longer than 5)
		music_set_playback_speed(2.2);
		play_star_wars_cantina_extended(buzzer, 2);
		music_set_playback_speed(1);
		break;
	case 3:
		play_star_wars_may_the_force(buzzer);
		break;
	default:
		music_set_playback_speed(1);
		play_star_wars(buzzer);
		break;
	}
	counter++;
	if (counter >= NUM_OF_SONGS)
	{
		counter = 0;
	}

	ledstrip_set_all(255, 255, 0);
}

/**
 * Will play extended versions of songs, if they exist. There is no time limit on how long songs may be.
 * Currently only runs one song (one switch case).
 */
void run_buzzer_extended(void)
{
	static int counter = 0;
	switch (counter)
	{
	case 0:
		music_set_playback_speed(1.5);
		play_star_wars_cantina_extended(buzzer, 4);
		music_set_playback_speed(1);
		break;
	case 1:
		play_star_wars_may_the_force_extended(buzzer, 4);
		break;
	case 2:
		break;
	default:
		music_set_playback_speed(1.5);
		play_star_wars_cantina_extended(buzzer, 1);
		music_set_playback_speed(1);
		break;
	}
	counter++;
	if (counter >= NUM_OF_LONG_SONGS)
	{
		counter = 0;
	}

	ledstrip_set_all(255, 255, 0);
}

void sleep_buzzer(void)
{
	pwm_shutdown();
}