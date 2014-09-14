#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "i2cslaves.h"
#include "cap_button_driver.h"

#define status_led_pin 	(1<<PB3)

#define status_ledOff()		PORTB &=~status_led_pin
#define status_ledOn()		PORTB |= status_led_pin
#define status_ledToggle()	PORTB ^= status_led_pin

#define KEY_UP			1
#define KEY_DOWN		2

char touch_keys_task(unsigned char *keys);

void delay_ms(uint16_t ms)
{
  uint16_t t;
  for(t=0; t<=ms; t++)
	_delay_ms(1);
}

void init(){
	DDRB = status_led_pin;
	status_ledOn();

	delay_ms(500);		// make sure power is stable

	sei();

	i2c_slaves_init();

	status_ledOff();
}

int main()
{
	init();

	signed char volume=VOLUME_INIT;
	unsigned char keys;

	while(1)
	{
		//pcf8574_task_test();
		if (touch_keys_task(&keys)){
			switch(keys){
			case KEY_UP:
				if (volume<VOLUME_MAX)
					volume++;
				break;
			case KEY_DOWN:
				if (volume>VOLUME_MIN)
					volume--;
				break;
			case (KEY_DOWN|KEY_UP):
				break;
			}

			volume_set(volume);
		}
	}
}

char touch_keys_task(unsigned char *keys){	// implemented with real keys connected to pcf8574
	static unsigned char key_ref=0;
	char result=0;
	unsigned char key_tmp=0;

	// -------- TODO replace only this code with touch keys -------
	unsigned char keyPCF = pcf8574_get(0);

	if (keyPCF==pcf_key1)
		key_tmp = KEY_DOWN;
	else if (keyPCF==pcf_key4)
		key_tmp = KEY_UP;
	// -------------

	if ((key_tmp!=key_ref)&&(key_tmp)) result=1;

	*keys = key_tmp;
	key_ref = key_tmp;
	return result;
}

