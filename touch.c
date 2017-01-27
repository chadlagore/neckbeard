#include <stdio.h>
#include <unistd.h>
#include "touch.h"


/*
 * This function runs the initial handshake with the touchscreen controller
 * and informs the unit to start accepting touch.
 */
void init_touch(void) {

	AR1100_CONTROL = 0x15; //perhaps this should go first and 0x03 shouldn't happpen... check datasheet
	AR1100_BAUD = 0x05; //anything >4 means a baud rate of 9600 (recommended by datasheet)

	usleep(5000);

	//touch_enable sequence
	send_char(0x55);
	send_char(0x01);
	send_char(0x12);

	usleep(5000);

}

/*
 * Sends a particular char to the AR1100, useful for initializing the touch
 * screen.
 *
 * @param c a char value
 */
void send_char(char c){
	while ((AR1100_STATUS & AR1100_TX_MASK) != 0x02);
	AR1100_TX = c;
}


int screen_touched(void){
	if (AR1100_RX_MASK & AR1100_STATUS) {
		if ((AR1100_RX & 0x81) == 0x81) {
			return 1;
		}
	}

	return 0;
}


void wait_for_touch(){
	printf("Waiting for screen to be untouched\n");
	while(!screen_touched());
}


Point get_press(void) {

	Point p1;

	wait_for_touch();
	printf("waited for touch\n");
	WAIT_FOR_AR1100_STATUS
	printf("status enabled code to continue\n");
	p1.x = AR1100_RX;

	WAIT_FOR_AR1100_STATUS

	p1.x += AR1100_RX << 7;

	WAIT_FOR_AR1100_STATUS

	p1.y = AR1100_RX;

	WAIT_FOR_AR1100_STATUS
	
	p1.y += AR1100_RX << 7;

	p1.x = (int) ((p1.x) / 4090.0 * 800.0);

	p1.y = (int) ((p1.y - 30) / 4070.0 * 480.0);

	return p1;
}


/*
 * This function waits for a pen up command, and consequently returns
 * the X,Y coordinate in a Point struct.
 *
 * @return  Point p1, current position of finger upon release.
 */
Point get_release(void){

	Point p1;

	while(1) {
		if(AR1100_RX_MASK & AR1100_STATUS){
			if(AR1100_RX == 0x80){
				break;
			}
		}
	}

	WAIT_FOR_AR1100_STATUS

	p1.x = AR1100_RX;

	WAIT_FOR_AR1100_STATUS

	p1.x += AR1100_RX << 7;

	WAIT_FOR_AR1100_STATUS

	p1.y = AR1100_RX;

	WAIT_FOR_AR1100_STATUS

	p1.y += AR1100_RX << 7;

	p1.x = (int) ((p1.x) / 4090.0 * 800.0);

	p1.y = (int) ((p1.y - 30) / 4070.0 * 480.0);

	return p1;
}


void test_touchscreen(void){

	printf("Testing the touchscreen...\n");
	init_touch();
	printf("Touchscreen successfully initalized\n");

	while(1){
		Point indicator = get_press();

		printf("Where did the bad man touch you?\n");
		printf("He touched me at: (%d, %d)\n", indicator.x, indicator.y);
	}
}
