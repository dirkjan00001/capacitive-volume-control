/*
 * cap_button_driver.h
 *
 *  Created on: Sep 14, 2014
 *      Author: dirk-jan
 */

#ifndef CAP_BUTTON_DRIVER_H_
#define CAP_BUTTON_DRIVER_H_

#define AVG_ARRAY_SIZE		20	// Size of the array for averaging.
								// Required memory size for 2 keys:
								// 			15 + 6*AVG_ARRAY_SIZE

#define KEYS				2

#define BUTTON1_PRESSED		1
#define BUTTON2_PRESSED		2


void cap_button_init(void);
unsigned char cap_button_task(void);	// returns if one or more buttons are pressed


#endif /* CAP_BUTTON_DRIVER_H_ */
