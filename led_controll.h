/*
 * led_controll.h
 *
 *  Created on: 2012.10.04.
 *      Author: pentike
 */

#ifndef LED_CONTROLL_H_
#define LED_CONTROLL_H_

#include <inttypes.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define RED OCR1A
#define GREEN OCR2A
#define BLUE OCR1B
#define WHITE OCR2B

#define RED_PIN PB1
#define GREEN_PIN PB2
#define BLUE_PIN PB3
#define WHITE_PIN PD3

#define FADE_DELAY_MS 1

static uint8_t _red;
static uint8_t _blue;
static uint8_t _green;

void init_led_pins();
void set_color(uint8_t red, uint8_t green, uint8_t blue);
void fade_to_color(uint8_t red, uint8_t green, uint8_t blue);
uint8_t get_red();
uint8_t get_green();
uint8_t get_blue();
#endif /* LED_CONTROLL_H_ */
