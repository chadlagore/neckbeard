#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nios_system.h"
#include "touch.h"
#include "bluetooth.h"
#include "graphics.h"
#include "wifi.h"
#include "altera_up_avalon_character_lcd.h"

int main(void) {
	printf("Hello from Nios II!\n");

	// /* open the Character LCD port */
	// alt_up_character_lcd_dev * char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	// if ( char_lcd_dev == NULL) {
	// 	printf ("Error: could not open character LCD device\n");
	// } else {
	// 	printf ("Opened character LCD device\n");
	// }
	//
	// /* Initialize the character display */
	// alt_up_character_lcd_init (char_lcd_dev);
	//
	// /* Write "Devin Meckling" in the first row */
	// alt_up_character_lcd_string(char_lcd_dev, "Devin Meckling");
	//
	// /* Write "hates quartus" in the second row */
	// char second_row[] = "hates quartus\0";
	// alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	// alt_up_character_lcd_string(char_lcd_dev, second_row);

	// /* draw a line across the screen in RED at y coord 100 and from x = 0 to 799 */
	// for(i = 0; i < 800; i ++) {
	// 	WriteAPixel(i, 100, RED);
	// }
	//
	// /* read the pixels back and make sure we read 2 (RED) to prove it's working */
	// for(i = 0; i < 800; i ++) {
	// 	printf("Colour value (i.e. pallette number) = %d at [%d, 100]\n", ReadAPixel(i, 100), i);
	// }

	printf("Initializing wifi... ");
	init_wifi();

	const char *wifi_message = "print(\"hello world\")\0";
	printf("Sending %s to wifi\n", wifi_message);
	sendstring_wifi(wifi_message);

	printf("Recieving message from wifi:\n");


	int i;
	for (i = 0; i < 10000; i++) {
		printf("%s", (char) getchar_wifi());
	}

	return 0;
}
