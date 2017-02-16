#include "distance.h"
#include "touch.h"
#include "gps.h"
#include "wifi.h"
#include "gui.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* UTILITY FUNCTIONS */

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

/* END UTILITY FUNCTIONS */


float read_dist() {
    long actual_cycles = BIT_FACTOR * CYCLES;
    float microseconds = actual_cycles / CLOCK_SPEED_MHZ;

    // To save bits, we divide the cycle count and
    // lose resolution. Multiply back up by `BitFactor'.
    // From manual:
    //             Distance(us) in cm = us / 58;
    return microseconds / 58;
}


/*
 * Count the number of cars that pass every
 * "seconds" number of seconds
 * It needs to be passed the base_dist, which is the
 * distance from the sensor to the ground when there is
 * no car passing.
 * THIS FUNCTION WILL BLOCK UNTIL THE USER CLICKS EXIT
 */
void count_cars(int seconds, float base_dist) {
	struct gps_packet *gps_pkt = gps_packet_create();
	clock_t start = clock();
	clock_t delta;
	float dist_read;
	int car_count = 0, x, y;
	Point touch_piont;
	char car_count_str[4], command[100];


	while (1) {
		touch_piont = get_press();
		x = touch_piont.x;
		y = touch_piont.y;

		if (EXIT_BUTTON) {
			free(gps_pkt);
			main_menu();
			return;
		}

		/* Get distance from sensor */
		dist_read = read_dist();

		/* Check if there is a car passing based on dist */
		if (base_dist - dist_read >= CAR_DETECTION_THRESHOLD) {
			car_count++;
		}

		/* Calculate number of seconds we have been reading for */
		delta = (clock() - start)/CLOCKS_PER_SEC;

		if (delta < seconds) {
			/* Convert car count to string */
			itoa(car_count, car_count_str);

			update_gps_data(gps_pkt);
			sprintf(command, "s('%s','%s','%s','%s')\0",
				car_count_str, gps_pkt->latitude, gps_pkt->longitude, gps_pkt->utc_time);

			printf("Sending command: %s\n", command);
			sendstring_wifi(command);

			start = clock();
		}
	}
}


// initialize
void init_distance(void) {
	DISTANCE_BAUD = 0x1F;
}

int get_distance(void)
{
	//while ((DISTANCE_STATUS & 0x2) != 0x2);
	return DISTANCE_RXDATA;
}

int test_for_distance_data(void) {
	 // Test Rx bit in 6850 serial comms chip status register
	 // if RX bit is set return TRUE, otherwise return FALSE
	volatile unsigned short int status = (volatile unsigned short int) DISTANCE_STATUS;
	return status & 0x1;

}
