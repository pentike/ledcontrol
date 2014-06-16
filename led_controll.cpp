/*
 * led_controll.c
 *
 *  Created on: 2012.10.04.
 *      Author: pentike
 */
#include "led_controll.h"




void init_led_pins() {
	//init timer 1 for 8 bit PWM
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	TCCR1B = _BV(WGM12) | _BV(CS10);
	//init timer 2 for 8 bit PWM
	TCCR2A = _BV(COM2A1)|_BV(WGM20);
	TCCR2B = _BV(CS20);

	//enable output pins
	DDRB = _BV(RED_PIN) | _BV(GREEN_PIN) | _BV(BLUE_PIN);
}

void set_color(uint8_t red, uint8_t green, uint8_t blue) {
	RED = red;
	GREEN = green;
	BLUE = blue;

	_red=red;
	_green=green;
	_blue=blue;
}

void fade_to_color(uint8_t red, uint8_t green, uint8_t blue) {
	while (red != RED || green != GREEN || blue != BLUE) {
		int16_t delta_red = red - RED;
		int16_t delta_green = green - GREEN;
		int16_t delta_blue = blue - BLUE;

//		printf("red: %d, newred: %d, delta: %d\n",RED, red, delta_red);
		if (delta_red != 0)
			RED = (delta_red > 0) ? RED + 1 : RED - 1;
		if (delta_green != 0)
			GREEN = (delta_green > 0) ? GREEN + 1 : GREEN - 1;
		if (delta_blue != 0)
			BLUE = (delta_blue > 0) ? BLUE + 1 : BLUE - 1;
		_delay_ms(FADE_DELAY_MS);
	}
	_red=red;
	_green=green;
	_blue=blue;
}

uint8_t get_red() { return _red; }
uint8_t get_green() { return _green; }
uint8_t get_blue() { return _blue; }
