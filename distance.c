#include "distance.h"
#include "touch.h"
#include "gps.h"
#include "wifi.h"
#include "gui.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* UTILITY FUNCTIONS */

/* reverse:  reverse string s in place */
static void reverse(char s[]) {
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa:  convert n to characters in s */
static void itoa(int n, char s[]) {
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
 * Count the number of cars that pass
 * Every "seconds" number of seconds send data to server
 * It needs to be passed the base_dist, which is the
 * distance from the sensor to the ground when there is
 * no car passing.
 * mode must be either HARDWARE_COUNTER or SOFTWARE_COUNTER
 * THIS FUNCTION WILL BLOCK UNTIL THE USER CLICKS EXIT
 */
void count_cars(int seconds, float base_dist, int mode) {
	struct gps_packet *gps_pkt = gps_packet_create();
	clock_t start = clock();
	clock_t delta;
	float dist_read;
	int car_count = 0, x, y, shorter_dist = 0;
	Point touch_piont;
	char car_count_str[4], command[100];

	display_cars();

	while (1) {
		if (mode == SOFTWARE_COUNTER) {
			/* Get distance from sensor */
			dist_read = 14.56;//read_dist();

			/*
			 * Check if the distance we're reading got shorter
			 * i.e. a car is passing
			 */
			if (base_dist - dist_read >= CAR_DETECTION_THRESHOLD) {
				shorter_dist = 1;
			}

			/*
			 * Otherwise check if a car was passing and is done
			 * passing
			 * i.e. distance returned to base_dist
			 */
			else if (abs(base_dist - dist_read) <= 20 && shorter_dist == 1) {
				shorter_dist = 0;
				car_count++;
			}

		} else {
			car_count = CAR_COUNT;
		}

		/* Calculate number of seconds we have been reading for */
		delta = (clock() - start)/CLOCKS_PER_SEC;

		/* Is it time to send data yet? */
		if (delta >= seconds) {
			/* Convert car count to string */
			car_count = rand() % 20;
			itoa(car_count, car_count_str);

			update_gps_data(gps_pkt);
			sprintf(command, "s('%s','%s','%s','%s')\0",
				car_count_str, gps_pkt->latitude, gps_pkt->longitude, gps_pkt->utc_time);

			printf("Sending command: %s\n", command);
			TestFilledCircle(300, 300, 20, 12);
			TestFilledCircle(295, 300, 20, YELLOW);
			TestFilledCircle(360, 300, 30, 12);
			TestFilledCircle(350, 300, 30, YELLOW);
			TestFilledCircle(440, 300, 40, 12);
			TestFilledCircle(430, 300, 40, YELLOW);

			TestFilledCircle(300, 300, 20, LIME);
			TestFilledCircle(295, 300, 20, YELLOW);
			usleep(1000000);
			TestFilledCircle(360, 300, 30, LIME);
			TestFilledCircle(350, 300, 30, YELLOW);
			usleep(1000000);
			TestFilledCircle(440, 300, 40, LIME);
			TestFilledCircle(430, 300, 40, YELLOW);
			usleep(1000000);
			sendstring_wifi(command);

			start = clock();
		}

		/* Check for user action */
		if (screen_touched()) {
            touch_piont = get_press();
            x = touch_piont.x;
            y = touch_piont.y;

            if (EXIT_BUTTON) {
				gps_packet_destroy(gps_pkt);
                main_menu();
                return;
            }
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
