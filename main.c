#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nios_system.h"
#include "touch.h"
#include "bluetooth.h"
#include "graphics.h"
#include "wifi.h"
#include "gps.h"
#include "distance.h"
#include "altera_up_avalon_character_lcd.h"

/*
 * A package containing data to be sent to the server
 * num_cars: the number of cars that have passed since the last
 				  packet was sent
 * latitude: the device's latitude
 * longitude: the device's longitude
 * pst: the pacific standard time at which this package was sent
 * time_span: the number of seconds over whidh the data in this package was collected
 */
struct package {
	int num_cars;
	float latitude;
	float longitude;
	char *pst;
	int time_span;
};

/*
 * Convert the packet to a JSON string to be
 * sent to the server
 */
char *package_to_str(struct package *pkg) {
	char *json_str = malloc(sizeof(char)*80);
	char *base_str = "{\"num_cars\" :     , \"latitude\" :          , \"PST\" :         , \"time_span\" :     }";
	char *num_chars_label = "{\"num_cars\" : ";
	char *latitude_label = ", \"latitude\" : ";

	/* Fill in values in the base JSON string using package data */
	int i;
	for (i = 0; i < 80; i++) {
		/* If we are not looking at a colon just copy it to the JSON string */
		if (base_str[i] != ':') {
			json_str[i] = base_str[i];
		}
		/* Otherwise we need to insert the data */
		else {
			// sprintf(str, "%d", aInt);
		}
	}
}

int main() {
	printf("Data boys lets go!\n");

	/* Initialize everyting! */
	init_gps();
	init_wifi();
	init_touch();
	init_distance();
	init_bluetooth();

	/* Inifitely loop and get data */
	while (1) {

		/* If the distance sensor is ready to send data to the server send it */
		int *
		if (get_distance_data()) {

		}
	}

	return 0;
}
