#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "nios_system.h"
#include "touch.h"
#include "bluetooth.h"
#include "graphics.h"
#include "wifi.h"
#include "gps.h"
#include "distance.h"
#include "data_package.h"
#include "Fill.h"
#include "tests.h"
#include "gui.h"
#include "distance.h"
#include "altera_up_avalon_character_lcd.h"

#define ONE_SECOND 				1000
#define CAR_COUNT_INTERVAL		10
#define SOFTWARE_COUNTER  		1


int main() {
	/* Run tests */
	// test_wifi();
	// test_gps();
	// test_send_data_package();
	//init_bluetooth();
	//reset_bluetooth();
	//test_bluetooth();
	init_bluetooth();
	float base_dist = HEX0 + HEX1*10 + HEX2*100;

	char string[10];


	char buffer[1024];
	while(1){
		main_menu();
		char received_character = get_char();
		if (get_char() == 'c') {
			printf("received character: %c", received_character);
			calibrate();
		}
		else {
			printf("received character: %c", received_character);
		}
	}
//	while(1){
//		base_dist = HEX0 + HEX1*10 + HEX2* 100;
//		sprintf(string, "$%.2f cm\n", base_dist);
//		printf(string);
//		sendstring_bluetooth(string);
//		usleep(1000000);
//	}
	//reset_bluetooth();
	//test_bluetooth();
	//transmit_string("hello there idiot");

//	int car_count, x, y;
//	float base_dist = 30.0;//read_dist();
//	Point point_touched;
//
//	printf("Initializing...\n");
//	init_gps();
//	init_wifi();
//	init_touch();
//	startup_screen();
//	main_menu();
//	plot_data();
//	printf("Done Initializing\n");
//
//	while (1) {
//		point_touched = get_press();
//		x = point_touched.x;
//		y = point_touched.y;
//
//		if (GPS_BUTTON) {
//			display_gps();
//		}
//
//		else if (CALIBRATE_BUTTON) {
//			calibrate();
//		}
//
//		else if (CAR_BUTTON) {
//			count_cars(CAR_COUNT_INTERVAL, base_dist, SOFTWARE_COUNTER);
//		}
//
//		else if (PLOT_BUTTON){
//			plot_data();
//		}
//	}
//
//	printf("\nDONE\n");
//	while (1) {};
//	return 0;
}
