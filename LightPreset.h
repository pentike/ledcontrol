/*
 * LightPreset.h
 *
 *  Created on: 2014.05.25.
 *      Author: pentike
 */

#ifndef LIGHTPRESET_H_
#define LIGHTPRESET_H_

#include "led_controll.h"
#include "Arduino.h"



void preset_roundrobin(int mx, uint8_t next_channel_after_ticks);
uint8_t track_silence(int mx);


#endif /* LIGHTPRESET_H_ */
