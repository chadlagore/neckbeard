#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
//#include "nios_system.h"
#include "touch.h"
//#include "bluetooth.h"
#include "graphics.h"
#include "graphics_test.h"
#include "gui.h"
//#include "gps.h"
//#include "altera_up_avalon_character_lcd.h"


void main(void) {
	startup_screen();


	//testClearScreen(RED);
	//write_test_screen();
	//Text(150, 240, LIME, RED, "FUCKING RIDICULOUS", 0);
//
//	int x1 = 100;
//	int y1 = 100;
//	int x2 = 200;
//	int y2 = 200;
//
//	testButton(100, 100, 200, 200, WHITE, LIME, RED, "PEACE");
//
//	init_touch();
//
//	while(1){
//		Point indicator = get_press();
//
//		int x = indicator.x;
//		int y = indicator.y;
//
//		char str_x[4];
//		char str_y[4];
//
//		snprintf(str_x, sizeof(str_x), "%d", indicator.x);
//		snprintf(str_y, sizeof(str_y), "%d", indicator.y);
//
//		char str[80];
//		strcpy(str, "Touched at: (");
//		strcat(str, str_x);
//		strcat(str, ", ");
//		strcat(str, str_y);
//		strcat(str, ")\n");
//
//		//printf("Touched at: (%d, %d)\n", indicator.x, indicator.y);
//
//		while (indicator.x > x1 && indicator.x < x2 && indicator.y > y1 && indicator.y < y2 && !screen_release()){
//			Text(150, 240, LIME, BLACK, str, 0);
//		}
//
//		Text(150, 240, BLACK, BLACK, str, 0);
//
//
//		WAIT_FOR_TOUCH
//	}

}
