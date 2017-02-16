#include "distance.h"
#include <time.h>


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
 * Count the number of cars that pass in
 * the next "seconds" seconds and return it
 * It needs to be passed the base_dist, which is the
 * distance from the sensor to the ground when there is
 * no car passing.
 * THIS FUNCTION WILL BLOCK FOR THE NUMBER OF
 * SECONDS SPECIFIED!
 */
int count_cars(int seconds, float base_dist) {
	clock_t start = clock();
	clock_t delta;
	float dist_read;
	int car_count = 0;

	do {
		/* Get distance from sensor */
		dist_read = read_dist();

		/* Check if there is a car passing based on dist */
		if (base_dist - dist_read >= CAR_DETECTION_THRESHOLD) {
			car_count++;
		}

		/* Calculate number of seconds we have been reading for */
		delta = (clock() - start)/CLOCKS_PER_SEC;
	} while (delta < seconds);

	return car_count;
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

int test_for_distance_data(void)
{
	 // Test Rx bit in 6850 serial comms chip status register
	 // if RX bit is set return TRUE, otherwise return FALSE
	volatile unsigned short int status = (volatile unsigned short int) DISTANCE_STATUS;
	return status & 0x1;

}
