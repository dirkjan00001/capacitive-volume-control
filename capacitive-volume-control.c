/*-------------------------------------*\
| TinyStepper Unipolar Stepper Driver	|
| ATTiny2313-based unipolar driver for	|
| 6-wire or 8-wire stepper motors.		|
|										|
| Serial and i2c interface				|
| 										|
| Adam Honse (amhb59@mail.mst.edu/		|
|			  calcprogrammer1@gmail.com)|
| 3/31/2012								|
\*-------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "i2cslaves.h"

#define status_led_pin 	(1<<PB3)

#define status_ledOff()		PORTB &=~status_led_pin
#define status_ledOn()		PORTB |= status_led_pin
#define status_ledToggle()	PORTB ^= status_led_pin

void delay_ms(uint16_t ms)
{
  uint16_t t;
  for(t=0; t<=ms; t++)
	_delay_ms(1);
}

void init(){
	DDRB = status_led_pin;

	status_ledOn();

	sei();

	i2c_slaves_init();

	delay_ms(500);
	status_ledOff();
}

int main()
{
	init();

	while(1)
	{
/*		delay_ms(500);
		pcf8574_put(pcf_led4);
		status_ledOn();

		delay_ms(500);
		pcf8574_put(pcf_led1);
		status_ledOff();*/


		unsigned char key = pcf8574_get(0);
		pcf8574_put(key);
	}
}
