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
#include "graphics_test.h"
#include "tests.h"
#include "altera_up_avalon_character_lcd.h"


int main() {
	/* Run tests */
	// test_wifi();
	// test_gps();
	// test_send_data_package();

	printf("Initializing...\n");
	init_gps();
	init_wifi();
	printf("Done Initializing\n");

	struct gps_packet *gps_pkt = gps_packet_create();
	char *command = malloc(sizeof(char)*100);
	char *response = malloc(sizeof(char)*500);

	while (1) {
		update_gps_data(gps_pkt);
		sprintf(command, "s('%s','%s','%s','%s')\0",
			"25", gps_pkt->latitude, gps_pkt->longitude, gps_pkt->utc_time);

		printf("Sending command: %s\n", command);
		sendstring_wifi(command);
		// receivestring_wifi(response, 500, 's', ')');
		// printf("Response: %s\n", response);

		usleep(10000000);
	}

	// sendstring_wifi("check_wifi('hey')\0");
	// putchar_wifi('\n');
	// receivestring_wifi(buf, 100, 'c', ')');
	// printf("%s\n", buf);
	// usleep(5000000);
	// printf("Sent message\n");

	printf("\nDONE\n");
	while (1) {};
	return 0;
}
