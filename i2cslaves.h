#ifndef _I2CSLAVES_H
#define _I2CSLAVES_H   1

#define VOLUME_MIN		0
#define VOLUME_MAX		79
#define VOLUME_INIT		3



#define pcf8574			0x70      			// I/O expander address
#define PT2257			0x88				// digital volume chip

#define PT2257_2_channel_1dB	0xD0
#define PT2257_2_channel_10dB	0xE0
#define PT2257_mute_on			0x79
#define PT2257_mute_off			0x78


#define pcf_led4		0x01
#define pcf_led3		0x02
#define pcf_led2		0x04
#define pcf_led1		0x08
#define pcf_ledsoff		0x00

#define pcf_key1		0x01
#define pcf_key2		0x02
#define pcf_key3		0x04
#define pcf_key4		0x08
#define pcf_keys		0xF0


#define I2C_READ    1
#define I2C_WRITE   0


void i2c_slaves_init();

void volume_set(signed char volume);
void PT2257_set_volume(unsigned char minus_volume);

void pcf8574_put(char leds);
unsigned char pcf8574_get(unsigned char key_led);		// 0 for key status, 1 for led status
void pcf8574_task_test(void);

#endif
