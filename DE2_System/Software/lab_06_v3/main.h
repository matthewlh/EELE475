/*
 * main.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Matthew Handley
 *      		David Keltgen
 */

#ifndef MAIN_H_
#define MAIN_H_


/*** includes ***/

#include <stdio.h>
#include <unistd.h>

/*** defines ***/
#define Switches (volatile int *) 0x01001150
#define LEDs 	 (volatile int *) 0x01001140

#define PWM1_BASE_ADDRESS 0x010010C0
#define PWM1_CTRL ((volatile int *) PWM1_BASE_ADDRESS)
#define PWM1_PERIOD ((volatile int *) (PWM1_BASE_ADDRESS + 4))
#define PWM1_NEUTRAL ((volatile int *)( PWM1_BASE_ADDRESS + 8))
#define PWM1_LARGEST ((volatile int *)( PWM1_BASE_ADDRESS + 12))
#define PWM1_SMALLEST ((volatile int *)( PWM1_BASE_ADDRESS + 16))
#define PWM1_ENABLE ((volatile int *) (PWM1_BASE_ADDRESS + 20))




/*** prototypes ***/
void 	WriteLCD		( char* string1, char* string2);
int 	GetActiveSwitch	();

#endif /* MAIN_H_ */