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
	int last_switch_num;

	/* init */
	*LEDs = 0x00000000;


	*PWM1_CTRL 		= 0x000002;
	*PWM1_PERIOD 	= 0x0f4240;
	*PWM1_NEUTRAL 	= 0x0124f8;
	*PWM1_LARGEST 	= 0x0186a0;
	*PWM1_SMALLEST 	= 0x00c350;
	*PWM1_ENABLE 	= 0x000001;

	/*** Block 1 ***/
	if(*PWM1_CTRL == 0x000002)
		printf("PWM1_CTRL readback ok\n");
	else
		printf("PWM1_CTRL readback FAILED!  0x%08X\n", *PWM1_CTRL);

	if(*PWM1_PERIOD == 0x0f4240)
		printf("PWM1_PERIOD readback ok\n");
	else
		printf("PWM1_PERIOD readback FAILED!\n");

	if(*PWM1_NEUTRAL == 0x0124f8)
		printf("PWM1_NEUTRAL readback ok\n");
	else
		printf("PWM1_NEUTRAL readback FAILED!\n");

	if(*PWM1_LARGEST == 0x0186a0)
		printf("PWM1_LARGEST readback ok\n");
	else
		printf("PWM1_LARGEST readback FAILED!\n");

	if(*PWM1_SMALLEST == 0x00c350)
		printf("PWM1_SMALLEST readback ok\n");
	else
		printf("PWM1_SMALLEST readback FAILED!\n");

	if(*PWM1_ENABLE == 0x000001)
		printf("PWM1_ENABLE readback ok\n");
	else
		printf("PWM1_ENABLE readback FAILED!  0x%08X\n", *PWM1_ENABLE);


	/*** Block 2 ***/
	printf("\n");

	if(*PWM1_CTRL_R == 0x000002)
		printf("PWM1_CTRL_R readback ok\n");
	else
		printf("PWM1_CTRL_R readback FAILED!  0x%08X\n", *PWM1_CTRL_R);

	if(*PWM1_PERIOD_R == 0x0f4240)
		printf("PWM1_PERIOD_R readback ok\n");
	else
		printf("PWM1_PERIOD_R readback FAILED!  0x%08X\n", *PWM1_PERIOD_R);

	if(*PWM1_NEUTRAL_R == 0x0124f8)
		printf("PWM1_NEUTRAL_R readback ok\n");
	else
		printf("PWM1_NEUTRAL_R readback FAILED!  0x%08X\n", *PWM1_NEUTRAL_R);

	if(*PWM1_LARGEST_R == 0x0186a0)
		printf("PWM1_LARGEST_R readback ok\n");
	else
		printf("PWM1_LARGEST_R readback FAILED!  0x%08X\n", *PWM1_LARGEST_R);

	if(*PWM1_SMALLEST_R == 0x00c350)
		printf("PWM1_SMALLEST_R readback ok\n");
	else
		printf("PWM1_SMALLEST_R readback FAILED!  0x%08X\n", *PWM1_SMALLEST_R);

	if(*PWM1_ENABLE_R == 0x000001)
		printf("PWM1_ENABLE_R readback ok\n");
	else
		printf("PWM1_ENABLE_R readback FAILED!  0x%08X\n", *PWM1_ENABLE_R);



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
				*LEDs = 0x00000004;
				*PWM1_ENABLE = 0x00000001;
				*PWM1_CTRL = 127;
				break;
			default:
				*LEDs = 0x00000000;
				*PWM1_CTRL = *PWM1_CTRL +1;
			}
		}

}



