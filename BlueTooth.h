/*
 * BlueTooth.h
 *
 *  Created on: 2014.05.26.
 *      Author: pentike
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "Messenger.h"
#include "SoftwareSerial.h"
#include "led_controll.h"
#include "Arduino.h"

void bt_command_mode();
void set_bt_device_name();
void disconnect();
void onMessage();


#endif /* BLUETOOTH_H_ */
