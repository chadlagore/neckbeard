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


int main() {
	int car_count, x, y;
	char char_received, bluetooth_msg[50];
	float base_dist = HEX0 + HEX1*10 + HEX2*100;//read_dist();
	Point point_touched;

	printf("Initializing...\n");
	init_gps();
	init_wifi();
	init_touch();
	init_bluetooth();
	startup_screen();
	main_menu();
	srand(time(NULL));
	printf("Done Initializing\n");

	while (1) {
		point_touched = get_press();
		x = point_touched.x;
		y = point_touched.y;

		if (GPS_BUTTON) {
			get_release();
			display_gps();
		}

		else if (CALIBRATE_BUTTON) {
			get_release();
			calibrate(&base_dist);
		}

		else if (CAR_BUTTON) {
			get_release();
			count_cars(CAR_COUNT_INTERVAL, base_dist, SOFTWARE_COUNTER);
		}

		else if (PLOT_BUTTON){
			get_release();
			plot_data(base_dist);
		}

		char_received = get_char();

		if (char_received == 'C') {
			calibrate(&base_dist);
			printf("Received command: %c\n", char_received);
			sprintf(bluetooth_msg, "$C%f\n\0", base_dist);
			printf("Sending reply: %s\n", bluetooth_msg);
			sendstring_bluetooth(bluetooth_msg);
		}
	}

	return 0;
}
