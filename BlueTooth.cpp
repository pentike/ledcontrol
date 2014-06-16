/*
 * BlueTooth.cpp
 *
 *  Created on: 2014.05.26.
 *      Author: pentike
 */
#include "BlueTooth.h"

Messenger msg = Messenger();
SoftwareSerial serial = SoftwareSerial(2, 4);

void bt_command_mode() {
	serial.write('+');
	delay(100);
	serial.write('+');
	delay(100);
	serial.write('+');
	delay(100);
	serial.write('\r');
	delay(100);
}

void set_bt_device_name() {
	serial.write('A');
	delay(100);
	serial.write('T');
	delay(100);
	serial.write('N');
	delay(100);
	serial.write('=');
	delay(100);
	serial.write('p');
	delay(100);
	serial.write('e');
	delay(100);
	serial.write('n');
	delay(100);
	serial.write('t');
	delay(100);
	serial.write('i');
	delay(100);
	serial.write('k');
	delay(100);
	serial.write('e');
	delay(100);
	serial.write(' ');
	delay(100);
	serial.write('l');
	delay(100);
	serial.write('e');
	delay(100);
	serial.write('d');
	delay(100);
	serial.write('\r');
	delay(200);
}

void disconnect() {
	bt_command_mode();

	serial.write('A');
	delay(100);
	serial.write('T');
	delay(100);
	serial.write('H');
	delay(100);
	serial.write('\r');
}

void onMessage() {
	char op = 0;
	op = msg.readChar();
	// s - set color, f - fade to color
	if (op == 's' || op == 'f') {
		int red = msg.readInt();
		int green = msg.readInt();
		int blue = msg.readInt();
		if (op == 'f') {
			fade_to_color(red, green, blue);
		} else if (op == 's') {
			set_color(red, green, blue);
		}
		String color = "colorChange " + String(red) + " " + String(green) + " "
				+ String(blue) + "\n";
		serial.print(color);
	}
	// q - query color
	else if (op == 'q') {
		String color = "currentColor " + String(get_red()) + " " + String(
				get_green()) + " " + String(get_blue()) + "\n";
		serial.print(color);
	} else {
		serial.print("Unknown command.");
		serial.print(op);
		serial.print("\n");
	}
}
