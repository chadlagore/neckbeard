#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
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

#define CAR_COUNT_INTERVAL		10
#define TRUE 					1
#define FALSE 					0
#define SECONDS_THRESHOLD		5

int dist_streaming = FALSE;
int count_streaming = FALSE;
clock_t stream_start;
clock_t delta;


static void do_bluetooth(float *base_dist, struct gps_packet *gps_pkt) {
	char bluetooth_msg[50];
	char char_received = get_char();
	float dist = read_dist();
	int car_count = 0, shortest_dist = 0;
	int received_command = TRUE;

	switch (char_received) {
		case 'D':
			dist_streaming = TRUE;
			stream_start = clock();
			sprintf(bluetooth_msg, "$D%0.0f\n", dist);
			sendstring_bluetooth(bluetooth_msg);
			break;

		case 'O':
			count_streaming = TRUE;
			dist_streaming = FALSE;
			stream_start = clock();

		case 'C':
			dist_streaming = FALSE;
			count_streaming = FALSE;
			*base_dist = read_dist();
			sprintf(bluetooth_msg, "$C%d\n", (int)*base_dist);
			sendstring_bluetooth(bluetooth_msg);
			break;

		case 'S':
			dist_streaming = FALSE;
			count_streaming = FALSE;
			update_gps_data(gps_pkt);
			sprintf(bluetooth_msg, "$S%0.0f,Connected,%d,%s,%s\n",
				dist, (int)*base_dist, gps_pkt->latitude, gps_pkt->longitude);
			sendstring_bluetooth(bluetooth_msg);
			break;

		case 'X':
			dist_streaming = FALSE;
			count_streaming = FALSE;
			break;

		default:
			received_command = FALSE;

			if (dist_streaming &&
				((float)(clock() - stream_start)/CLOCKS_PER_SEC) > 1.0) {
				stream_start = clock();
				sprintf(bluetooth_msg, "$D%0.0f\n", dist);
				printf("dist_streaming data: %s", bluetooth_msg);
				sendstring_bluetooth(bluetooth_msg);
			}

			else if (count_streaming) {
				/*
				* Check if the distance we're reading got shorter
				* i.e. a car is passing
				*/
				if (*base_dist - dist >= CAR_DETECTION_THRESHOLD) {
					shorter_dist = 1;
				}

				/*
				* Otherwise check if a car was passing and is done
				* passing
				* i.e. distance returned to base_dist
				*/
				else if (abs(*base_dist - dist) <= 10 && shortest_dist == 1) {
					shortest_dist = 0;
					car_count++;
				}
				/* Calculate number of seconds we have been reading for */
				delta = (clock() - stream_start)/CLOCKS_PER_SEC;

				/* Is it time to send data yet? */
				if (delta >= SECONDS_THRESHOLD) {
					sprintf(bluetooth_msg, "$%d\n", car_count);
					sendstring_bluetooth(bluetooth_msg);
					car_count = 0;
					stream_start = clock();
				}
			}
	}

	if (received_command) {
		printf("Received command: %c\n", char_received);
		printf("Sent reply: %s\n", bluetooth_msg);
	}
}


int main() {
	int x, y, err;
	float base_dist = read_dist();
	Point point_touched;
	struct gps_packet *gps_pkt;

	printf("Initializing...\n");

	init_gps();
	init_wifi();
	init_touch();
	init_bluetooth();
	startup_screen();
	main_menu();
	srand(time(NULL));

	gps_pkt = gps_packet_create();

	printf("Done Initializing\n");

	while (1) {
		if (screen_touched()) {
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
		}

		do_bluetooth(&base_dist, gps_pkt);
	}

	return 0;
}
