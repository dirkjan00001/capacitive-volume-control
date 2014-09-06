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

#define status_led_pin 	(1<<PB2)

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

	status_ledOff();

	sei();

	i2c_slaves_init();

	delay_ms(500);
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
/*
inline void process_serial_message()
{
	if(serial_available() > 2)
	{
		status_led_on();
		
		char buffer[3];
		serial_read_buffer(buffer, 3);

		switch(buffer[0])
		{		
			//Set I2C Address
			case 0x22:
				usi_i2c_slave_address = buffer[1];
				eeprom_write_byte((uint8_t*)1, usi_i2c_slave_address);
				break;

			//Read I2C Address
			case 0x23:
				serial_transmit_byte(usi_i2c_slave_address);
				break;

			//Send I2C Write
			case 0x24:
				fill_i2c_buffer_from_serial(buffer[1], buffer[2], 0);
				serial_transmit_byte(USI_I2C_Master_Start_Transmission(serial_i2c_buffer, buffer[1]+1));
				break;

			//Send I2C Read
			case 0x25:
				{
					char addr = buffer[2] << 1 | 1;
					serial_i2c_buffer[0] = addr;
					USI_I2C_Master_Start_Transmission(serial_i2c_buffer, buffer[1]+1);
					for(char i = 1; i <= buffer[1]; i++)
					{
						serial_transmit_byte(serial_i2c_buffer[i]);
					}
				}
				break;
		}
		status_led_off();	
	}
}


void fill_i2c_buffer_from_serial(char len, char addr, char rw)
{
	//Set R/W bit of address
	addr = addr << 1 | rw;

	//Put address into i2c buffer
	serial_i2c_buffer[0] = addr;

	for(char i = 1; i <= len; i++)
	{
		while(serial_available() < 1);
		serial_i2c_buffer[i] = serial_read();
	}
}*/
