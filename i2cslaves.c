#include "i2cslaves.h"
#include "usi_i2c_master.h"

void i2c_slaves_init(){
	//master init
	DDR_USI  |= (1 << PORT_USI_SDA) | (1 << PORT_USI_SCL);
	PORT_USI |= (1 << PORT_USI_SCL);
	PORT_USI |= (1 << PORT_USI_SDA);

	USIDR = 0xFF;
	USICR = (0 << USISIE) | (0 << USIOIE) | (1 << USIWM1) | (0 << USIWM0) | (1 << USICS1) | (0 << USICS0) | (1 << USICLK) | (0 << USITC);
	USISR = (1 << USISIF) | (1 << USIOIF) | (1 << USIPF)  | (1 << USIDC)  | (0x00 << USICNT0);

}

void pcf8574_put(char leds)
{
	char buffer[2];
	buffer[0]=pcf8574|I2C_WRITE;
	buffer[1]=(~leds)|pcf_keys;
	USI_I2C_Master_Start_Transmission(buffer, 2);
}

unsigned char pcf8574_get(unsigned char key_led)
{
	unsigned char ret = 0;
	char buffer[2];
	buffer[0]=pcf8574|I2C_READ;
	USI_I2C_Master_Start_Transmission(buffer, 2);
	ret=~buffer[1];

	if (key_led)	// read led satus
	{
		ret &= ~pcf_keys;
	}
	else			// read keys satus
	{
		ret &= pcf_keys;
		ret >>= 4;
	}
	return ret;
}
