/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 * Author(s):	Matthew Handley
 * 				David Keltgen
 * Date:		2014-09-09
 *
 */

#include <stdio.h>

#define Switches (volatile int *) 	0x01005030
#define LEDs 	 (int *) 			0x01005020

int main()
{
	printf("Hello from Nios II!\n");
	printf("This is a test.\n");

	while (1)
	{
		*LEDs = *Switches;
	}
}


