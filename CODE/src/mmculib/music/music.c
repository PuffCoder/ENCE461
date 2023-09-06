/**
 * @file music.c
 * @author Jamie Thomas
 * @brief Music module that allows peizo buzzer to play musical notes and prebuilt songs. 
 * @date 2023-05-19
 * 
 *   ========= ALL MUSIC AND NOTES ARE BLOCKING =========
 * 
 *   4 Bars roughly every 5 seconds. 
 *   2075 in each bar: Will use 2000
 *   125 ms per semi quaver. (1*)         Will use   75 + 50 rest
 *   *2 quaver         = 250              Will use  200 + 50 rest
 *   *3 dotted quaver  = 375              Will use  325 + 50 rest
 *   *4 crotchet       = 500              Will use  450 + 50 rest
 *   *8 minim          = 1000             Will use  950 + 50 rest
 */

#include "music.h"

static pwm_t buzzer;
static double speed = 1;

void play_note(music_pitch_t note_freq, music_notes_t note_lenth);
void play_rest_note(music_notes_t note_lenth);
void play_dual_note(music_pitch_t note_freq1, music_pitch_t note_freq2, music_notes_t note_lenth);
void play_note_tuplet(music_pitch_t note_freq1, music_pitch_t note_freq2, music_pitch_t note_freq3, music_notes_t note_above_lenth);
void play_note_tuplet_lights(music_pitch_t note_freq1, music_pitch_t note_freq2, music_pitch_t note_freq3, music_notes_t note_above_length, uint8_t r, uint8_t g, uint8_t b, bool ramp_up);


static void music_buzzer_init(pwm_t new_buzzer)
{
	buzzer = new_buzzer;
}

void music_set_playback_speed(double new_speed)
{
	speed = new_speed;
}

/**
 * @brief Plays Star Wars, "Imperial March". Length: ~5s
 * 
 * @param buzzer Buzzer to play music on. 
 */
void
play_star_wars_imperial_march(pwm_t buzzer)
{

	// Initialise buzzer
	music_buzzer_init(buzzer);

	// Bar 1
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_G7, CROTCHET);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_G7, CROTCHET);
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_G7, CROTCHET);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_Eb7, QUAVER_DOT);
	ledstrip_set_all(255, 100, 0);
	play_note(NOTE_Bb7, SEMIQUAVER);
	

	// Bar 2
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_G7, CROTCHET);
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_Eb7, QUAVER_DOT);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_Bb7, SEMIQUAVER);
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_G7, MINIM);
	
	// Bar 3
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_D8, CROTCHET);
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_D8, CROTCHET);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_D8, CROTCHET);
	ledstrip_set_all(255, 30, 30);
	play_note(NOTE_Eb8, QUAVER_DOT);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_Bb7, SEMIQUAVER);

	// Bar 4
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_Gb7, CROTCHET);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_Eb7, QUAVER_DOT);
	ledstrip_set_all(255, 30, 0);
	play_note(NOTE_Bb7, SEMIQUAVER);
	ledstrip_set_all(255, 0, 0);
	play_note(NOTE_G7, MINIM);



}

/**
 * @brief Plays Star Wars main theme song. Length: ~5s
 * 
 * @param buzzer Buzzer to play music on. 
 */
void
play_star_wars(pwm_t buzzer)
{

	// Initialise buzzer
	music_buzzer_init(buzzer);

	// Prebar (1/4)
	ledstrip_set_all(10, 10, 10);
	play_note_tuplet(NOTE_G6, NOTE_G6, NOTE_G6, CROTCHET);

	// Bar 1
	ledstrip_set_all(0, 0, 255);
	play_note(NOTE_C7, MINIM);
	ledstrip_set_all(200, 10, 255);
	play_note(NOTE_G7, MINIM);

	// Bar 2
	ledstrip_set_all(10, 10, 30);
	play_note_tuplet(NOTE_F7, NOTE_E7, NOTE_D7, CROTCHET);
	ledstrip_set_section(255, 255, 255, SECTION_1);
	ledstrip_set_section(255, 255, 255, SECTION_2);
	ledstrip_set_section(255, 255, 255, SECTION_3);
	play_note(NOTE_C8, MINIM);
	ledstrip_set_section(0, 0, 255, SECTION_1);
	ledstrip_set_section(0, 0, 255, SECTION_2);
	ledstrip_set_section(0, 0, 255, SECTION_3);
	play_note(NOTE_G7, CROTCHET);

	// Bar 3
	ledstrip_set_all(10, 10, 30);
	play_note_tuplet(NOTE_F7, NOTE_E7, NOTE_D7, CROTCHET);
	ledstrip_set_section(255, 255, 255, SECTION_1);
	ledstrip_set_section(255, 255, 255, SECTION_2);
	ledstrip_set_section(255, 255, 255, SECTION_3);
	play_note(NOTE_C8, MINIM);
	ledstrip_set_section(0, 0, 255, SECTION_1);
	ledstrip_set_section(0, 0, 255, SECTION_2);
	ledstrip_set_section(0, 0, 255, SECTION_3);
	play_note(NOTE_G7, CROTCHET);

	// Bar 4 (1/4 short of full bar)
	ledstrip_set_all(200, 10, 255);
	play_note_tuplet(NOTE_F7, NOTE_E7, NOTE_F7, CROTCHET);
	ledstrip_set_all(100, 100, 255);
	play_note(NOTE_D7, MINIM);
}

/**
 * @brief Plays Star Wars "May the Force be With You" theme. Length: ~5s
 * 
 * @param buzzer Buzzer to play music on. 
 */
void
play_star_wars_may_the_force(pwm_t buzzer)
{

	// Initialise buzzer
	music_buzzer_init(buzzer);

	// Bar 1
	ledstrip_set_all(10, 10, 10);
	play_note(NOTE_C7, SEMIBREVE);

	// Bar 2
	ledstrip_set_all(20, 20, 20);
	play_note(NOTE_D7, MINIM_DOT);
	ledstrip_set_all(20, 20, 20);
	ledstrip_set_section(200, 10, 200, SECTION_1);
	play_note(NOTE_Eb7, QUAVER);
	ledstrip_set_section(200, 10, 200, SECTION_2);
	play_note(NOTE_F7, QUAVER);

	// Bar 3
	ledstrip_set_section(200, 10, 200, SECTION_3);
	play_note(NOTE_Eb7, SEMIBREVE);

	// Bar 4
	ledstrip_set_all(20, 20, 20);
	play_note(NOTE_G6, MINIM_DOT);
	ledstrip_set_all(0, 0, 0);
	delay_ms(10);
	ledstrip_set_all(20, 20, 20);
	play_note(NOTE_G6, CROTCHET);

}

/**
 * @brief Plays Star Wars "Cantina Band". Length: ~5s
 * 
 * @param buzzer Buzzer to play music on. 
 */
void
play_star_wars_cantina(pwm_t buzzer)
{

	// Initialise buzzer
	music_buzzer_init(buzzer);

	// Bar 1
	ledstrip_set_section(0, 255, 0, SECTION_1);
	ledstrip_set_section(0, 100, 255, SECTION_2);
	ledstrip_set_section(0, 255, 0, SECTION_3);
	play_note(NOTE_A7, CROTCHET);
	ledstrip_set_section(0, 100, 255, SECTION_1);
	ledstrip_set_section(0, 255, 0, SECTION_2);
	ledstrip_set_section(0, 100, 255, SECTION_3);
	play_note(NOTE_D8, CROTCHET);
	ledstrip_set_section(0, 255, 0, SECTION_1);
	ledstrip_set_section(0, 100, 255, SECTION_2);
	ledstrip_set_section(0, 255, 0, SECTION_3);
	play_note(NOTE_A7, CROTCHET);
	ledstrip_set_section(0, 100, 255, SECTION_1);
	ledstrip_set_section(0, 255, 0, SECTION_2);
	ledstrip_set_section(0, 100, 255, SECTION_3);
	play_note(NOTE_D8, CROTCHET);

	// Bar 2
	ledstrip_set_section(0, 255, 0, SECTION_1);
	ledstrip_set_section(0, 100, 255, SECTION_2);
	ledstrip_set_section(0, 255, 0, SECTION_3);
	play_note(NOTE_A7, QUAVER);
	ledstrip_set_section(0, 100, 255, SECTION_1);
	ledstrip_set_section(0, 255, 0, SECTION_2);
	ledstrip_set_section(0, 100, 255, SECTION_3);
	play_note(NOTE_D8, CROTCHET);
	ledstrip_set_section(0, 255, 0, SECTION_1);
	ledstrip_set_section(0, 0, 0, SECTION_2);
	ledstrip_set_section(0, 0, 0, SECTION_3);
	play_note(NOTE_A7, QUAVER);
	ledstrip_set_section(0, 255, 0, SECTION_1);
	ledstrip_set_section(0, 255, 0, SECTION_2);
	ledstrip_set_section(0, 0, 0, SECTION_3);
	play_rest_note(QUAVER);
	ledstrip_set_section(0, 255, 0, SECTION_1);
	ledstrip_set_section(0, 255, 0, SECTION_2);
	ledstrip_set_section(0, 255, 0, SECTION_3);
	play_note(NOTE_Ab7, QUAVER);
	ledstrip_set_all(0, 255, 0);
	play_note(NOTE_A7, CROTCHET);
	// Bar 3
	ledstrip_set_all(0, 255, 0);
	play_note(NOTE_A7, QUAVER);
	play_note(NOTE_Ab7, QUAVER);
	ledstrip_set_all(0, 170, 0);
	play_note(NOTE_A7, QUAVER);
	play_note(NOTE_G7, QUAVER);
	ledstrip_set_all(0, 90, 0);
	play_rest_note(QUAVER);
	play_note(NOTE_Gb7, QUAVER);
	ledstrip_set_all(0, 0, 0);
	play_note(NOTE_G7, QUAVER);
	play_note(NOTE_Gb7, QUAVER);
	// Bar 4
	ledstrip_set_all(0, 90, 0);
	play_note(NOTE_F7, CROTCHET_DOT);
	ledstrip_set_all(0, 255, 0);
	play_note(NOTE_D7, MINIM_QUAVER);

}


/**
 * @brief Plays Star Wars "May the Force be With You" theme.
 * 
 * @param buzzer Buzzer to play music on. 
 */
void
play_star_wars_may_the_force_extended(pwm_t buzzer, int length)
{

	// Bars 1-4
	play_star_wars_may_the_force(buzzer);

	if (length > 1)
	{
		// Bar 5
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(20, 50, 20);
		play_note(NOTE_C7, MINIM_DOT);
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(30, 50, 30);
		play_note(NOTE_D7, CROTCHET);

		// Bar 6
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(30, 100, 30);
		play_note(NOTE_Eb7, CROTCHET);
		ledstrip_set_all(100, 20, 20);
		play_note(NOTE_G6, CROTCHET);
		ledstrip_set_all(30, 30, 100);
		play_note_tuplet_lights(NOTE_Eb7, NOTE_C7, NOTE_G7, MINIM, 180, 180, 100, true);

		// Bar 7
		ledstrip_set_all(200, 160, 100);
		play_note(NOTE_F7, SEMIBREVE);

		// Bar 8
		play_note(NOTE_F7, MINIM);
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(50, 50, 80);
		play_note(NOTE_G6, MINIM);
	}
	if (length > 2)
	{
		// Bar 9
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(60, 60, 60);
		play_note(NOTE_C7, MINIM_DOT);
		ledstrip_set_all(140, 60, 60);
		play_note(NOTE_D7, CROTCHET);

		// Bar 10
		ledstrip_set_all(60, 180, 60);
		play_note(NOTE_Eb7, CROTCHET_DOT);
		ledstrip_set_all(60, 60, 60);
		play_note(NOTE_G6, QUAVER);
		ledstrip_set_all(120, 60, 200);
		play_note(NOTE_G7, CROTCHET_DOT);
		ledstrip_set_all(60, 60, 60);
		play_note(NOTE_Eb7, QUAVER);

		// Bar 11
		ledstrip_set_all(255, 255, 255);
		play_note(NOTE_G8, SEMIBREVE);

		// Bar 12
		ledstrip_set_all(100, 155, 155);
		play_note(NOTE_C7, MINIM);
		play_note_tuplet_lights(NOTE_Eb7, NOTE_D7, NOTE_C7, MINIM, 255, 200, 255, true);
	}
	if (length > 3)
	{
		// Bar 13
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(140, 40, 140);
		play_note(NOTE_G7, MINIM_DOT);
		ledstrip_set_all(80, 40, 80);
		play_note(NOTE_Eb7, QUAVER);
		ledstrip_set_all(60, 40, 60);
		play_note(NOTE_C7, QUAVER);

		// Bar 14
		ledstrip_set_all(40, 40, 40);
		play_note(NOTE_G6, MINIM);
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(40, 40, 40);
		play_note(NOTE_G6, CROTCHET_DOT);
		ledstrip_set_all(0, 0, 0);
		delay_ms(10);
		ledstrip_set_all(40, 40, 40);
		play_note(NOTE_G6, QUAVER);

		// Bar 15
		ledstrip_set_all(200, 80, 200);
		play_note(NOTE_C7, SEMIBREVE);

	}

	

}

void
play_star_wars_cantina_extended(pwm_t buzzer, int length)
{
	// Bars 1-4
	play_star_wars_cantina(buzzer);

	if (length > 1) 
	{
		// Bar 5
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 100, 255, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, CROTCHET);
		ledstrip_set_section(0, 100, 255, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 100, 255, SECTION_3);
		play_note(NOTE_D8, CROTCHET);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 100, 255, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, CROTCHET);
		ledstrip_set_section(0, 100, 255, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 100, 255, SECTION_3);
		play_note(NOTE_D8, CROTCHET);
		// Bar 6
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 100, 255, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, QUAVER);
		ledstrip_set_section(0, 100, 255, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 100, 255, SECTION_3);
		play_note(NOTE_D8, CROTCHET);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, QUAVER);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_rest_note(QUAVER);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_Ab7, QUAVER);
		ledstrip_set_all(0, 255, 0);
		play_note(NOTE_A7, CROTCHET);
		// Bar 7
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(255, 0, 0, SECTION_3);
		play_note(NOTE_G7, QUAVER);
		play_rest_note(QUAVER);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(255, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_G7, CROTCHET);
		ledstrip_set_section(255, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_G7, QUAVER);
		play_note(NOTE_Gb7, QUAVER);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(255, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_G7, CROTCHET);
		// Bar 8
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_C8, QUAVER);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_Bb7, CROTCHET);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, CROTCHET);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_G7, CROTCHET_DOT);
	}
	if (length > 2) 
	{
		// Bar 9
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 100, 255, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, CROTCHET);
		ledstrip_set_section(0, 100, 255, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 100, 255, SECTION_3);
		play_note(NOTE_D8, CROTCHET);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 100, 255, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, CROTCHET);
		ledstrip_set_section(0, 100, 255, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 100, 255, SECTION_3);
		play_note(NOTE_D8, CROTCHET);
		// Bar 10
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 100, 255, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_A7, QUAVER);
		ledstrip_set_section(0, 100, 255, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 100, 255, SECTION_3);
		play_note(NOTE_D8, CROTCHET);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_A7, QUAVER);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_rest_note(QUAVER);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 255, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_Ab7, QUAVER);
		ledstrip_set_all(0, 255, 0);
		play_note(NOTE_A7, CROTCHET);
		// Bar 11
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_C8, QUAVER);
		play_rest_note(QUAVER);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_note(NOTE_C8, CROTCHET);
		ledstrip_set_section(0, 255, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 0, 0, SECTION_3);
		play_note(NOTE_C8, QUAVER);
		play_note(NOTE_A7, QUAVER);
		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(0, 255, 0, SECTION_3);
		play_rest_note(QUAVER);
		play_note(NOTE_G7, QUAVER);
		// Bar 12
		ledstrip_set_all(0, 255, 0);
		play_note(NOTE_F7, CROTCHET_DOT);
		ledstrip_set_all(255, 0, 0);
		play_note(NOTE_D7, MINIM_QUAVER);
	}
	if (length > 3) 
	{
		// Bar 13
		ledstrip_set_all(0, 20, 0);
		play_note(NOTE_D7, MINIM);
		ledstrip_set_all(0, 80, 0);
		play_note(NOTE_F7, MINIM);
		// Bar 14
		ledstrip_set_all(0, 150, 0);
		play_note(NOTE_A7, MINIM);
		ledstrip_set_all(0, 255, 0);
		play_note(NOTE_C8, MINIM);
		// Bar 15
		ledstrip_set_section(100, 255, 0, SECTION_3);
		play_note(NOTE_Eb8, CROTCHET);
		ledstrip_set_section(100, 255, 0, SECTION_1);
		play_note(NOTE_D8, CROTCHET);
		ledstrip_set_section(100, 255, 0, SECTION_2);
		play_note(NOTE_Ab7, QUAVER);
		play_note(NOTE_A7, CROTCHET);
		ledstrip_set_all(0, 255, 0);
		play_note(NOTE_F7, QUAVER);
		// Bar 16
		play_note(NOTE_F7, SEMIBREVE);
	}
	
	

}


void
play_note(music_pitch_t note_freq, music_notes_t note_length)
{
	pwm_period_set (buzzer, PWM_PERIOD_DIVISOR(note_freq));
	pwm_start(buzzer);
	delay_ms(note_length / speed);
	pwm_stop(buzzer);
	delay_ms(MUSIC_END_OF_NOTE);
}

void
play_rest_note(music_notes_t note_length)
{
	pwm_stop(buzzer);
	delay_ms(note_length / speed);
	delay_ms(MUSIC_END_OF_NOTE);
}



/**
 * @brief Takes the time of "note_above_length". 
 * 
 * @param buzzer Buzzer to play note on. 
 * @param note_freq1 Note 1 pitch
 * @param note_freq2 Note 2 pitch
 * @param note_freq3 Note 3 pitch
 */
void
play_note_tuplet(music_pitch_t note_freq1, music_pitch_t note_freq2, music_pitch_t note_freq3, music_notes_t note_above_length)
{
	int new_note_length = (note_above_length + 25) / 3 - 25;
	play_note(note_freq1, new_note_length);
	play_note(note_freq2, new_note_length);
	play_note(note_freq3, new_note_length);
}

void
play_note_tuplet_lights(music_pitch_t note_freq1, music_pitch_t note_freq2, music_pitch_t note_freq3, music_notes_t note_above_length, uint8_t r, uint8_t g, uint8_t b, bool ramp_up)
{

	int new_note_length = (note_above_length + 25) / 3 - 25;
	ledstrip_clear_all();
	if (ramp_up) {
		
		ledstrip_set_section(r, g, b, SECTION_1);
		play_note(note_freq1, new_note_length);

		ledstrip_set_section(r, g, b, SECTION_2);
		play_note(note_freq2, new_note_length);

		ledstrip_set_section(r, g, b, SECTION_3);
		play_note(note_freq3, new_note_length);

	}
	else
	{
		ledstrip_set_section(r, g, b, SECTION_1);
		ledstrip_set_section(r, g, b, SECTION_2);
		ledstrip_set_section(r, g, b, SECTION_3);
		play_note(note_freq1, new_note_length);

		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(r, g, b, SECTION_2);
		ledstrip_set_section(r, g, b, SECTION_3);
		play_note(note_freq2, new_note_length);

		ledstrip_set_section(0, 0, 0, SECTION_1);
		ledstrip_set_section(0, 0, 0, SECTION_2);
		ledstrip_set_section(r, g, b, SECTION_3);
		play_note(note_freq3, new_note_length);
	}
	
	
}