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

#define ONE_SECOND 				1000
#define CAR_COUNT_INTERVAL		60
#define SOFTWARE_COUNTER  		1


/* reverse:  reverse string s in place */
void reverse(char s[]) {
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
	n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	if (sign < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}


int main() {
	/* Run tests */
	// test_wifi();
	// test_gps();
	// test_send_data_package();

	struct gps_packet *gps_pkt = gps_packet_create();
	char *command = malloc(sizeof(char)*100);
	char *response = malloc(sizeof(char)*500);
	char car_count_str[4];
	int car_count;
	float base_dist = read_dist(); // TODO: update when we have a calibration button

	printf("Initializing...\n");
	init_gps();
	init_wifi();
	update_gps_data(gps_pkt);
	printf("Done Initializing\n");

	while (1) {
		if (SOFTWARE_COUNTER) {
			car_count = count_cars(CAR_COUNT_INTERVAL, base_dist);
		} else {
			car_count = CAR_COUNT;
		}

		/* Convert car count to string */
		itoa(car_count, car_count_str);

		update_gps_data(gps_pkt);
		sprintf(command, "s('%s','%s','%s','%s')\0",
			car_count_str, gps_pkt->latitude, gps_pkt->longitude, gps_pkt->utc_time);

		printf("Sending command: %s\n", command);
		sendstring_wifi(command);
	}

	printf("\nDONE\n");
	while (1) {};
	return 0;
}
