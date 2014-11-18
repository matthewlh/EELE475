/*
 * main.h
 *
 *  Created on: Oct 28, 2014
 *      Author: w92p177
 */

#ifndef MAIN_H_
#define MAIN_H_

/*** includes ***/
#include <stdio.h>

/*** defines ***/
#define Switches (volatile int *) 0x01001150
#define LEDs 	 (volatile int *) 0x01001140

#define PWM1_BASE_ADDRESS 0x00000C00
#define PWM2_BASE_ADDRESS 0x00001400
#define BLOCK_SIZE (0x20*4)

#define PWM1_Block_1 	(PWM1_BASE_ADDRESS)
#define PWM1_CTRL 		((volatile int *) PWM1_Block_1)
#define PWM1_PERIOD 	((volatile int *) (PWM1_Block_1 + 4))
#define PWM1_NEUTRAL 	((volatile int *)( PWM1_Block_1 + 8))
#define PWM1_LARGEST 	((volatile int *)( PWM1_Block_1 + 12))
#define PWM1_SMALLEST 	((volatile int *)( PWM1_Block_1 + 16))
#define PWM1_ENABLE 	((volatile int *) (PWM1_Block_1 + 20))

#define PWM1_Block_2 	((PWM1_Block_1) +(BLOCK_SIZE))
#define PWM1_CTRL_R 	((volatile int *)  PWM1_Block_2)
#define PWM1_PERIOD_R 	((volatile int *) (PWM1_Block_2 + 4))
#define PWM1_NEUTRAL_R 	((volatile int *) (PWM1_Block_2 + 8))
#define PWM1_LARGEST_R 	((volatile int *) (PWM1_Block_2 + 12))
#define PWM1_SMALLEST_R ((volatile int *) (PWM1_Block_2 + 16))
#define PWM1_ENABLE_R 	((volatile int *) (PWM1_Block_2 + 20))

#define PWM2_Block_1 	(PWM2_BASE_ADDRESS)
#define PWM2_CTRL 		((volatile int *) PWM2_Block_1)
#define PWM2_PERIOD 	((volatile int *) (PWM2_Block_1 + 4))
#define PWM2_NEUTRAL 	((volatile int *)( PWM2_Block_1 + 8))
#define PWM2_LARGEST 	((volatile int *)( PWM2_Block_1 + 12))
#define PWM2_SMALLEST 	((volatile int *)( PWM2_Block_1 + 16))
#define PWM2_ENABLE 	((volatile int *) (PWM2_Block_1 + 20))

#define PWM2_Block_2 	((PWM2_Block_1) +(BLOCK_SIZE))
#define PWM2_CTRL_R 	((volatile int *)  PWM2_Block_2)
#define PWM2_PERIOD_R 	((volatile int *) (PWM2_Block_2 + 4))
#define PWM2_NEUTRAL_R 	((volatile int *) (PWM2_Block_2 + 8))
#define PWM2_LARGEST_R 	((volatile int *) (PWM2_Block_2 + 12))
#define PWM2_SMALLEST_R ((volatile int *) (PWM2_Block_2 + 16))
#define PWM2_ENABLE_R 	((volatile int *) (PWM2_Block_2 + 20))

/*** prototypes ***/
void 	WriteLCD		( char* string1, char* string2);
int 	GetActiveSwitch	();
void formatPWMStr(char* s1, char* s2);


#endif /* MAIN_H_ */
