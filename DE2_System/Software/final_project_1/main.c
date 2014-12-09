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
	*CRC_DWIDTH = 4;				// data will be written to SHIFT 4 bits at a time
	*CRC_PLEN 	= 16;				//
	*CRC_POLY 	= 0x1024;			//

	printf("CRC_CTRL:    0x%08X\n", *CRC_CTRL);
	printf("CRC_DWIDTH:  0x%08X\n", *CRC_DWIDTH);
	printf("CRC_PLEN:    0x%08X\n", *CRC_PLEN);
	printf("CRC_POLY:    0x%08X\n", *CRC_POLY);

	printf("\n");

	*CRC_CTRL |= CRC_CTRL_MSK_RESET;
	printf("CRC_CTRL:    0x%08X, CRC_RESULT:  0x%08X,  Shifted: 0x%08X, VWORD: 0x%08X, CRC_DEBUG:  0x%08X\n",
			*CRC_CTRL, *CRC_RESULT, *CRC_SHIFT, *CRC_VWORD, *CRC_DEBUG);
	*CRC_CTRL &= ~CRC_CTRL_MSK_RESET;
	printf("CRC_CTRL:    0x%08X, CRC_RESULT:  0x%08X,  Shifted: 0x%08X, VWORD: 0x%08X, CRC_DEBUG:  0x%08X\n",
			*CRC_CTRL, *CRC_RESULT, *CRC_SHIFT, *CRC_VWORD, *CRC_DEBUG);

	printf("\n");

	/* shift some data in */
	for(i = 1; i < 9; i++)
	{
		*CRC_SHIFT = i;

		printf("CRC_CTRL:    0x%08X, CRC_RESULT:  0x%08X,  Shifted: 0x%08X, VWORD: 0x%08X, CRC_DEBUG:  0x%08X\n",
					*CRC_CTRL, *CRC_RESULT, *CRC_SHIFT, *CRC_VWORD, *CRC_DEBUG);
	}

	*CRC_CTRL |= CRC_CTRL_MSK_START;

	printf("\n");

	printf("CRC_CTRL:    0x%08X, CRC_RESULT:  0x%08X,  Shifted: 0x%08X, VWORD: 0x%08X, CRC_DEBUG:  0x%08X\n",
				*CRC_CTRL, *CRC_RESULT, *CRC_SHIFT, *CRC_VWORD, *CRC_DEBUG);

	//while(1) {}

	return 0;
}
