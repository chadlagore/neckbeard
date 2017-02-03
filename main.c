#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "nios_system.h"
#include "touch.h"
#include "bluetooth.h"
#include "graphics.h"
#include "wifi.h"
#include "gps.h"
#include "distance.h"
#include "package.h"
#include "OutGraphicsCharFont2.h"
#include "Fill.h"
#include "altera_up_avalon_character_lcd.h"

int main() {
	printf("Data boys lets go!\n");

	/* Initialize everyting! */
	init_gps();
	init_wifi();
	init_touch();
	// init_distance();

	struct package *pkg = pkg_create();
	struct gps_packet *gps_pkt = gps_packet_create();
	clock_t data_start_time = clock();

	/* Inifitely loop and get data */
	while (1) {
		/* If the distance sensor is ready to send data to the server */
		if (rand() % 100 <= 1) {
			get_gps_data(gps_pkt);

			/* Fill package with data */
			pkg->num_cars = rand() % 100;
			pkg->latitude = gps_pkt->latitude;
			pkg->longitude = gps_pkt->longitude;
			pkg->pst = gps_pkt->local_time;
			pkg->time_span = (data_start_time - clock()) / CLOCKS_PER_SEC;

			/* Send package to wifi in JSON format */
			sendstring_wifi(pkg_to_json(pkg));

			/* Reset clock */
			data_start_time = clock();
		}
	}

	return 0;
}
