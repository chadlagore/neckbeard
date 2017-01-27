#include "nios_system.h"


/*******************************************************************************************
 ** Functions to support excercise 1.3
 *******************************************************************************************/

// set up 6850 Control Register to utilise a divide by 16 clock,
// set RTS low, use 8 bits of data, no parity, 1 stop bit,
// transmitter interrupt disabled
// program baud rate generator to use 115k baud
void Init_RS232(void)
{
	RS232_Baud = 0x15;
}

// poll Tx bit in 6850 status register. Wait for it to become '1'
// write 'c' to the 6850 TxData register to output the character
int putcharRS232(int c)
{
	while ((RS232_Status & 0x1) != 0x01);
	RS232_TxData = c;
	return c ;
}

// poll Rx bit in 6850 status register. Wait for it to become '1'
// read received character from 6850 RxData register.
int getcharRS232( void )
{
	while ((RS232_Status & 0x2) != 0x2);
	return (volatile unsigned short int)RS232_RxData;
}

// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int RS232TestForReceivedData(void)
{
	 // Test Rx bit in 6850 serial comms chip status register
	 // if RX bit is set, return TRUE, otherwise return FALSE
	volatile unsigned short int status = (volatile unsigned short int) RS232_Status;
	return status & 0x1;

}
