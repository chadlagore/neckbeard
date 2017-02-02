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
#include "package.h"
#include "altera_up_avalon_character_lcd.h"

int main() {
	printf("Data boys lets go!\n");

	/* Initialize everyting! */
	init_gps();
	init_wifi();
	init_touch();
	init_distance();

	/* Inifitely loop and get data */
	while (1) {

		/* If the distance sensor is ready to send data to the server send it */
		if (get_distance_data()) {

		}
	}

	return 0;
}
