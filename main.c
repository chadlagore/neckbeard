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
#include "altera_up_avalon_character_lcd.h"

#define ONE_SECOND 				1000
#define CAR_COUNT_INTERVAL		60
#define SOFTWARE_COUNTER  		1


int main() {
	/* Run tests */
	// test_wifi();
	// test_gps();
	// test_send_data_package();

	int car_count, x, y;
	//float base_dist = read_dist();
	Point point_touched;

	printf("Initializing...\n");
	init_gps();
	init_wifi();
	init_touch();
	startup_screen();
	main_menu();
	printf("Done Initializing\n");

	while (1) {
		point_touched = get_press();
		x = point_touched.x;
		y = point_touched.y;


		if (GPS_BUTTON) {
			display_gps();
		}

		else if (CALIBRATE_BUTTON) {
			calibrate();
			//base_dist = read_dist();
			main_menu();
		}

		else if (CAR_BUTTON) {
			printf("you pushed some dumb button");
			main_menu();

		//			if (SOFTWARE_COUNTER) {
		//				count_cars(CAR_COUNT_INTERVAL, base_dist);
		//			} else {
		//				// car_count = CAR_COUNT; TODO
		//			}
				}
	}

	printf("\nDONE\n");
	while (1) {};
	return 0;
}
