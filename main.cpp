#include "main.h"


uint8_t watchdog_timer = 0;
uint8_t watchdog_do_bluetooth_disconnect = 0;

uint8_t bass_count = 36;
uint8_t watchdog_run =0;

ISR(WDT_vect)
{
	if (watchdog_timer == 20) {
		watchdog_do_bluetooth_disconnect = 1;
		watchdog_timer = 0;

	} else {
		++watchdog_timer;
		watchdog_run=1;
	}
}

int main(void) {
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif

	setup();

	for (;;) {
		loop();
		if (serialEventRun)
			serialEventRun();
	}

	return 0;
}


void WDT_Init(void)
{
//disable interrupts
cli();
//reset watchdog
wdt_reset();
//set up WDT interrupt
WDTCSR = (1<<WDCE)|(1<<WDE);
//Start watchdog timer with 4s prescaller
WDTCSR = (1<<WDIE)|(1<<WDE)|(1<<WDP3);
//Enable global interrupts
sei();
}

void setup() {
	Serial.begin(19200);
//	serial.begin(19200);
	init_led_pins();
//	msg.attach(onMessage);

//	WDT_Init();

	delay(5000);
//	bt_command_mode();
	//    set_bt_device_name();
}


int read_max_volume_level() {
	int mn = 1024;
	int mx = 0;
	for (int i = 0; i < 1000; ++i) {
		int val = analogRead(5);
		mn = min(mn, val);
		mx = max(mx, val);
	}

//	Serial.print(mn);
//	Serial.print('\t');

	return mx;
}


#define DELAY 1000

void loop() {
//	fade_to_color(200, 0, 0);
//	delay(DELAY);
//	fade_to_color(0, 0, 0);
//	delay(DELAY);
//	fade_to_color(0, 200, 0);
//	delay(DELAY);
//	fade_to_color(0, 0, 0);
//	delay(DELAY);
//	fade_to_color(0, 0, 200);
//	delay(DELAY);
//	fade_to_color(0, 0, 0);
//	delay(DELAY);

	if (watchdog_run) {
		//light related stuff
		int rnd = rand();
		bass_count = rnd /1000;
		Serial.print(rnd);
		Serial.print('\t');

	Serial.print(bass_count);
	Serial.print('\t');
	watchdog_run=0;
	}

	int mx = read_max_volume_level();
	preset_roundrobin(mx,bass_count);
}
