/*************************************************************************
* file: main.c
* Name: Matthew Handley
* 		David Keltgen
* Date: 2014-11-25
*
*************************************************************************/

#include "uart_interrupt.h"
#include "count_binary.h"

int main(void)
{
	/* run button interrupt demo (does not return) */
	//count_binary();

	/* run UART interrupt demo (does not return) */
	uart_interrupts();

	return 0;
}
