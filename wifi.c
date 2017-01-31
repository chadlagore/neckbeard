#include "wifi.h"

void init_wifi() {
    WIFI_BAUD = 0x01;
}

void putchar_wifi(int c) {
    while ((WIFI_STATUS & 0x1) != 0x01);
	WIFI_TX = c;
}

int getchar_wifi(void) {
	while ((WIFI_STATUS & 0x2) != 0x2);
	return (volatile unsigned short int) WIFI_RX;
}

void sendstring_wifi(const char *string) {
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        putchar_wifi((int) string[i]);
    }

    /* Send carriage return and line feed */
    putchar_wifi((int) '\r');
    putchar_wifi((int) '\n');
}
