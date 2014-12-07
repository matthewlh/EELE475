/*************************************************************************
* file: main.c
* Name: Matthew Handley
* 		David Keltgen
* Date: 2014-11-25
*
*************************************************************************/

#include "main.h"

int main(void)
{
	/* local vars */
	int i;

	/* init CRC registers */
	*CRC_CTRL = CRC_CTRL_MSK_EN;	// set enable bit
	*CRC_DWIDTH = 3;				// data will be written to SHIFT 3 bits at a time
	*CRC_PLEN 	= 4;				//
	*CRC_POLY 	= 0x0B;				//

	printf("CRC_CTRL:    0x%08X\n", *CRC_CTRL);
	printf("CRC_DWIDTH:  0x%08X\n", *CRC_DWIDTH);
	printf("CRC_PLEN:    0x%08X\n", *CRC_PLEN);
	printf("CRC_POLY:    0x%08X\n", *CRC_POLY);

	printf("\n");

	/* shift in the data */
	*CRC_SHIFT = 0x4;
	printf("SHIFTED 0x4, CRC_RESULT:  0x%08X\n", *CRC_RESULT);
	*CRC_SHIFT = 0x5;
	printf("SHIFTED 0x5, CRC_RESULT:  0x%08X\n", *CRC_RESULT);
	*CRC_SHIFT = 0x3;
	printf("SHIFTED 0x3, CRC_RESULT:  0x%08X\n", *CRC_RESULT);
	*CRC_SHIFT = 0x2;
	printf("SHIFTED 0x2, CRC_RESULT:  0x%08X\n", *CRC_RESULT);
	*CRC_SHIFT = 0x3;
	printf("SHIFTED 0x3, CRC_RESULT:  0x%08X\n", *CRC_RESULT);

	printf("CRC_VWORD:  0x%08X\n", *CRC_VWORD);

	/* start the calculation */
	*CRC_CTRL |= CRC_CTRL_MSK_START;

	while( (*CRC_CTRL & CRC_CTRL_MSK_COMPLETE) != 1) {}

	printf("CRC_RESULT:  0x%08X\n", *CRC_RESULT);

	//while(1) {}

	return 0;
}
