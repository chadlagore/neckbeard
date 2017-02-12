#include "distance.h"

// initialize
void init_distance(void) {
	DISTANCE_BAUD = 0x1F;
}

int get_distance(void)
{
	//while ((DISTANCE_STATUS & 0x2) != 0x2);
	return DISTANCE_RXDATA;
}

int test_for_distance_data(void)
{
	 // Test Rx bit in 6850 serial comms chip status register
	 // if RX bit is set return TRUE, otherwise return FALSE
	volatile unsigned short int status = (volatile unsigned short int) DISTANCE_STATUS;
	return status & 0x1;

}
