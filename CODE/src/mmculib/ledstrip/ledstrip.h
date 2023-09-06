/**
 * @file ledstrip.h
 * @author Jamie Thomas
 * @brief 
 * @date 2023-05-24
 */

#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include "ledbuffer.h"

typedef struct color_struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct colors_struct
{
    color_t violet;
    color_t indigo;
    color_t blue;
    color_t green;
    color_t yellow;
    color_t orange;
    color_t red;
} colors_t;

typedef enum {

    SECTION_1, 
    SECTION_2,
    SECTION_3,
    SECTION_4,
    SECTION_5,
    SECTION_6,
    SECTION_7

}ledstrip_section_t;


void
ledstrip_init (void);

void ledstrip_set_all(uint8_t r, uint8_t g, uint8_t b);

void ledstrip_set_section(uint8_t r, uint8_t g, uint8_t b, ledstrip_section_t section);

void ledstrip_clear_all(void);

void ledstrip_rainbow(void);

void rainbow_init(void);

#endif /* LEDSTRIP_H */