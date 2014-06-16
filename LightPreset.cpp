/*
 * LightPreset.cpp
 *
 *  Created on: 2014.05.25.
 *      Author: pentike
 */
#include "LightPreset.h"

uint8_t silence = 0;
int  maximum = 0;
uint8_t prev;
uint8_t min_all_light = 0;
uint8_t min_light = 90;

uint8_t i,bass_ticks =0;
void preset_roundrobin(int mx, uint8_t next_channel_after_ticks) {
	int c=0;
	if (c<255) c=mx;
	if (mx>255 && maximum !=0) {
//		c = mx/maximum;
		c=255;
	}
	if (c < min_light)
		c = min_light;

	Serial.print('m');
	Serial.print(mx);
	Serial.print('\t');
	Serial.print(c);
	Serial.print('\t');

	if (c>100) {
		bass_ticks++;
	}
	if (bass_ticks>next_channel_after_ticks) { i++; bass_ticks=0; }

	Serial.print(bass_ticks);
	Serial.print('\t');

	if (i>7) i=0;

	//turn the lights on after silence
	if (track_silence(mx)>10) i=7;

	switch (i) {
		case 0: fade_to_color(min_all_light, min_all_light, c); break;
		case 1: fade_to_color(min_all_light, c, min_all_light); break;
		case 2: fade_to_color(c, min_all_light, min_all_light); break;
		case 3: fade_to_color(c, c, min_all_light); break;
		case 4: fade_to_color(min_all_light, c, c); break;
		case 5: fade_to_color(c, min_all_light, c); break;
		default: set_color(c,c,c);
	}
}

uint8_t maximum_watchdog =0;
uint8_t track_silence(int mx) {
	uint8_t ts=0;
	maximum = max(mx, maximum);

	if (++maximum_watchdog == 0) maximum=mx;

	if (mx < maximum/5) {
		++silence;
	} else {
		ts=silence;
		silence =0;
	}

	Serial.print(mx);
	Serial.print('\t');
//	Serial.print(maximum /5);
//	Serial.print('\t');
	Serial.print(silence);
	Serial.print('\n');

	return ts;
}

