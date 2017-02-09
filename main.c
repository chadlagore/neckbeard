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
	test_wifi();
	// test_gps();
	// test_send_data_package();

	// printf("Init\n");
	// init_wifi();
	// printf("Done init\n");
	// char *buf = malloc(sizeof(char)*100);
	// while (1) {
	// 	// sendstring_wifi("check_wifi('hey')\0");
	// 	putchar_wifi('\n');
	// 	receivestring_wifi(buf, 100, 'c', ')');
	// 	printf("%s\n", buf);
	// 	// usleep(5000000);
	// 	// printf("Sent message\n");
	// }

	printf("\nDONE\n");
	while (1) {};
	return 0;
}
