/*
 * main.c
 *
 *  Created on: Oct 14, 2014
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


	*PWM1_CTRL 		= -5;
	*PWM1_PERIOD 	= 0x000f4240;
	*PWM1_NEUTRAL 	= 0x000124f8;
	*PWM1_LARGEST 	= 0x000186a0;
	*PWM1_SMALLEST 	= 0x0000c350;
	*PWM1_ENABLE 	= 0x00000001;

	printf("PWM1_CTRL\n");
	printf("\twrote:          -5\n");
	printf("\treadback:       %d\n", *PWM1_CTRL);
	printf("\treadback alias: %d\n", *PWM1_CTRL_R);

	printf("PWM1_PERIOD\n");
	printf("\twrote:          0x000F4240\n");
	printf("\treadback:       0x%08X\n", *PWM1_PERIOD);
	printf("\treadback alias: 0x%08X\n", *PWM1_PERIOD_R);

	printf("PWM1_NEUTRAL\n");
	printf("\twrote:          0x000124F8\n");
	printf("\treadback:       0x%08X\n", *PWM1_NEUTRAL);
	printf("\treadback alias: 0x%08X\n", *PWM1_NEUTRAL_R);

	printf("PWM1_LARGEST\n");
	printf("\twrote:          0x000186A0\n");
	printf("\treadback:       0x%08X\n", *PWM1_LARGEST);
	printf("\treadback alias: 0x%08X\n", *PWM1_LARGEST_R);

	printf("PWM1_SMALLEST\n");
	printf("\twrote:          0x0000C350\n");
	printf("\treadback:       0x%08X\n", *PWM1_SMALLEST);
	printf("\treadback alias: 0x%08X\n", *PWM1_SMALLEST_R);

	printf("PWM1_ENABLE\n");
	printf("\twrote:          0x00000001\n");
	printf("\treadback:       0x%08X\n", *PWM1_ENABLE);
	printf("\treadback alias: 0x%08X\n", *PWM1_ENABLE_R);



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


