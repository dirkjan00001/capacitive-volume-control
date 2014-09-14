/*
 * cap_button_driver.c
 *
 *  Created on: Sep 14, 2014
 *      Author: dirk-jan
 */

#include "cap_button_driver.h"

void measure_cap(unsigned char cap[]);
void runningAverage(unsigned int cap_avg_sq[], unsigned int cap_dev_sq[], unsigned char cap[]);

// init pins etc.
void cap_button_init(void){
	// todo init pins
}

// returns if one or more buttons are pressed
unsigned char cap_button_task(void){
	unsigned char button_pressed = 0, cap[KEYS];
	static unsigned int cap_avg[KEYS]={0}, cap_dev[KEYS]={0};

	measure_cap(cap);

	runningAverage(cap_avg, cap_dev, cap);

	//todo determine which key is pressed


	return button_pressed;
}

void measure_cap(unsigned char cap[]){

	//todo implement function
}

// returns the squared average and the squared standard deviation
// todo test function
// required memory size for 2 keys = 2*AVG_ARRAY_SIZE + 2 + 2*2 + 2*2*AVG_ARRAY_SIZE + 4*2 + 1
// 								   = 15 + 6*AVG_ARRAY_SIZE
void runningAverage(unsigned int cap_avg_sq[], unsigned int cap_dev_sq[], unsigned char cap[])
{
  static unsigned char LM[AVG_ARRAY_SIZE][KEYS];      // LastMeasurements
  static unsigned char index = 0, count = 1;
  static unsigned int sum[KEYS] = {0};

  static unsigned int LM_sq[AVG_ARRAY_SIZE][KEYS];      // LastMeasurements
  static unsigned long sum_sq[KEYS] = {0};

  unsigned char i=0;

  for(i=0;i<KEYS;i++){
    sum[i] -= LM[index][i];
    LM[index][i] = (unsigned char) cap[i];
    sum[i] += (unsigned int) LM[index][i];

    sum_sq[i] -= LM_sq[index][i];
    LM_sq[index][i] = (unsigned int) cap[i] * (unsigned int) cap[i];
    sum_sq[i] += (unsigned long) LM_sq[index][i];
    unsigned long stdev_tmp = (sum_sq[i] - (unsigned long) sum[i] * (unsigned long) sum[i]) / (count * count);


    //cap_avg[i] = sum[i] / count;
    cap_avg_sq[i] = (unsigned int) sum_sq[i] / count;
    cap_dev_sq[i] = (unsigned int) stdev_tmp;
  }

  index ++;
  index = index % AVG_ARRAY_SIZE;

  if (count < AVG_ARRAY_SIZE) count++;
}
