/*
 * main.c
 *
 *  Created on: Oct 7, 2014
 *      Author(s): 	Matthew Handley
 *					David Keltgen
 */

#include <stdio.h>
#include "main.h"


void WriteLCD( char* string1, char* string2)
{
	FILE *lcd;
	lcd = fopen("/dev/lcd_display", "w");

	/* Write strings to the LCD. */
	if (lcd != NULL )
	{
		fprintf(lcd, "\n%s\n", string1);
		fprintf(lcd, "%s\n",string2);
	}
	else
	{
		printf("Could not open LCD file!\n");
	}

	fclose( lcd );
}

int GetActiveSwitch()
{
	int switchValues, i;
	int result = -1;

	switchValues = *Switches;
	for(i = 0; i < (sizeof(int) * 8);i++)
	{

		/* Mask the lower bit */
		if((switchValues & 1) == 1)
		{
			/* switch at Ith position is on */
			if(result == -1)
			{
				result = i;
			}
			else
			{
			   /* multiple switches are turned on */
			   return -1;
			}
		}

		/* Right shift switchValues 1 */
		switchValues >>= 1;
	 }
	return result;
}

int main()
{
	int switch_num;

	/* init */
	*LEDs = 0x00000000;

	*PWM1_PERIOD = 0x0f4240;
	*PWM1_NEUTRAL = 0x0124f8;
	*PWM1_LARGEST = 0x0186a0;
	*PWM1_SMALLEST = 0x00c350;


	while(1)
	{
		switch_num = GetActiveSwitch();

		switch(switch_num){
		case 0:
			*LEDs = 0x00000001;
			*PWM1_ENABLE = 0x00000001;
			*PWM1_CTRL = -128;
			break;
		case 1:
			*LEDs = 0x00000002;
			*PWM1_ENABLE = 0x00000001;
			*PWM1_CTRL = 0;
			break;
		case 2:
			*LEDs = 0x00000003;
			*PWM1_ENABLE = 0x00000001;
			*PWM1_CTRL = 128;
			break;
		default:
			*LEDs = 0x00000000;
			*PWM1_ENABLE = 0x00000000;
		}
	}
}


