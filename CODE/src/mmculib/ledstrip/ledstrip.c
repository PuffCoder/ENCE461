/**
 * @file ledstrip.c
 * @author Jamie Thomas
 * @brief 
 * @date 2023-05-24
 */

#include "ledstrip.h"

#define NUM_LEDS 21
#define BRIGHTNESS 0.6

static ledbuffer_t *leds;

colors_t colors;

color_t get_color(int color) {
	switch (color) {
		case 0: return colors.violet;
		case 1: return colors.indigo;
		case 2: return colors.blue;
		case 3: return colors.green;
		case 4: return colors.yellow;
		case 5: return colors.orange;
		case 6: return colors.red;
		default: return (color_t) { // WHITE
			.red = 255*BRIGHTNESS,
			.green = 255*BRIGHTNESS,
			.blue = 255*BRIGHTNESS
		};
		}
}

void
ledstrip_init (void)
{
	leds = ledbuffer_init (LEDTAPE_PIO, NUM_LEDS);
	colors.violet = (color_t) {
		.red = 148*BRIGHTNESS,
		.green = 0,
		.blue = 211*BRIGHTNESS
  	};
	colors.indigo = (color_t) {
		.red = 75*BRIGHTNESS,
		.green = 0,
		.blue = 130*BRIGHTNESS
  	};
	colors.blue = (color_t) {
		.red = 0,
		.green = 0,
		.blue = 255*BRIGHTNESS
  	};
	colors.green = (color_t) {
		.red = 0,
		.green = 255*BRIGHTNESS,
		.blue = 0
  	};
	colors.yellow = (color_t) {
		.red = 255*BRIGHTNESS,
		.green = 255*BRIGHTNESS,
		.blue = 0
  	};
	colors.orange = (color_t) {
		.red = 255*BRIGHTNESS,
		.green = 127*BRIGHTNESS,
		.blue = 0
  	};
	colors.red = (color_t) {
		.red = 255*BRIGHTNESS,
		.green = 0,
		.blue = 0
  	};
}

void ledstrip_set_all(uint8_t r, uint8_t g, uint8_t b)
{

	for (int n = 0; n < NUM_LEDS; n++) {

		ledbuffer_set(leds, n, r, g, b);

	}
	ledbuffer_write(leds);

}


void ledstrip_set_section(uint8_t r, uint8_t g, uint8_t b, ledstrip_section_t section)
{

	for (int n = (0 + section); n < NUM_LEDS; n = n + 3) {
		
		ledbuffer_set(leds, n, r, g, b);

	}
	ledbuffer_write(leds);

}

void ledstrip_clear_all(void) 
{

	ledbuffer_clear(leds);

	ledbuffer_write(leds);

}

void ledstrip_rainbow()
{
	ledbuffer_advance(leds, 1);
	ledbuffer_write(leds);
}

void rainbow_init()
{
	for (int n = 0; n < NUM_LEDS; n++) {
		color_t color = get_color((n%7));
		ledbuffer_set(leds, n, color.red, color.green, color.blue);
	}
	ledbuffer_write(leds);
}

