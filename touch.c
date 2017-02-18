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

	/* touch_enable sequence */
	sendchar_touch(0x55);
	sendchar_touch(0x01);
	sendchar_touch(0x12);

	usleep(5000);

}

/*
 * Sends a particular char to the AR1100, useful for initializing the touch
 * screen.
 *
 * @param c a char value
 */
void sendchar_touch(char c){
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

int screen_release(void){
	if (AR1100_RX_MASK & AR1100_STATUS) {
		if ((AR1100_RX & 0x80) == 0x80) {
			return 1;
		}
	}

	return 0;
}


void wait_for_touch(){
	while(!screen_touched());
}

void wait_for_release(){
	while(!screen_release());
}


Point get_press(void) {

	Point p1;

	wait_for_touch();

	WAIT_FOR_TOUCH

	p1.x = AR1100_RX;

	WAIT_FOR_TOUCH

	p1.x += AR1100_RX << 7;

	WAIT_FOR_TOUCH

	p1.y = AR1100_RX;

	WAIT_FOR_TOUCH

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

	WAIT_FOR_TOUCH

	p1.x = AR1100_RX;

	WAIT_FOR_TOUCH

	p1.x += AR1100_RX << 7;

	WAIT_FOR_TOUCH

	p1.y = AR1100_RX;

	WAIT_FOR_TOUCH

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

		printf("Touched at: (%d, %d)\n", indicator.x, indicator.y);

		wait_for_release();

		Point indicator2 = get_release();

		printf("Released at: (%d, %d) \n", indicator2.x, indicator2.y);

		WAIT_FOR_TOUCH
	}
}
