/**
 * @file music.h
 * @author Jamie Thomas
 * @brief Music module that allows peizo buzzer to play musical notes and prebuilt songs. 
 * @date 2023-05-19
 */

#ifndef MUSIC_H
#define MUSIC_H

#include "config.h"
#include "delay.h"
#include "pwm.h"
#include "ledstrip.h"

#define NUM_OF_SONGS 4
#define NUM_OF_LONG_SONGS 2

/*
 *   4 Bars roughly every 5 seconds. 
 *   2075 in each bar: Will use 2000
 *   125 ms per semi quaver. (1*)         Will use  100 + 50 rest
 *   *2 quaver         = 250              Will use  225 + 50 rest
 *   *3 dotted quaver  = 375              Will use  350 + 50 rest
 *   *4 crotchet       = 500              Will use  475 + 50 rest
 *   *8 minim          = 1000             Will use  975 + 50 rest
 */
#define MUSIC_END_OF_NOTE 50

#define QUAVER_TUPLET 111

typedef enum music_notes_enum {
    SEMIQUAVER = 100,
    QUAVER = 225,
    QUAVER_DOT = 350, // 3 * semiquaver
    CROTCHET = 475,
    CROTCHET_DOT = 700,
    MINIM = 975,
    MINIM_QUAVER = 1250, // For special useage in Cantina
    MINIM_DOT = 1475,
    SEMIBREVE = 1975
} music_notes_t;


typedef enum music_pitch_enum {
    NOTE_G6 = 1568,
    NOTE_Ab6 = 1661,
    NOTE_A6 = 1760,
    NOTE_Bb6 = 1864,
    NOTE_B6 = 1976,
    NOTE_C7 = 2093,
    NOTE_Db7 = 2217,
    NOTE_D7 = 2349,
    NOTE_Eb7 = 2489,
    NOTE_E7 = 2637,
    NOTE_F7 = 2793,
    NOTE_Gb7 = 2959,
    NOTE_G7 = 3136,
    NOTE_Ab7 = 3322,
    NOTE_A7 = 3520,
    NOTE_Bb7 = 3729,
    NOTE_B7 = 3951,
    NOTE_C8 = 4186,
    NOTE_Db8 = 4435,
    NOTE_D8 = 4699,
    NOTE_Eb8 = 4978,
    NOTE_E8 = 5274,
    NOTE_F8 = 5588,
    NOTE_Gb8 = 5919,
    NOTE_G8 = 6272
} music_pitch_t;


void music_set_playback_speed(double new_speed);

// Songs
void play_star_wars_imperial_march(pwm_t buzzer);
void play_star_wars(pwm_t buzzer);
void play_star_wars_cantina(pwm_t buzzer);
void play_star_wars_may_the_force(pwm_t buzzer);

// Extended Songs
void play_star_wars_cantina_extended(pwm_t buzzer, int length);
void play_star_wars_may_the_force_extended(pwm_t buzzer, int length);




#endif /* MUSIC_H */