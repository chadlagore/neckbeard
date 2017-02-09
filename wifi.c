#include "wifi.h"

void init_wifi() {
    WIFI_CONTROL = 0x15;
    WIFI_BAUD = 0x01;

    putchar_wifi('\n');
    putchar_wifi('\n');
}

void putchar_wifi(char c) {
    while ((WIFI_STATUS & 0x2) != 0x2);
	WIFI_TX = c;
}

char getchar_wifi(void) {
	while ((WIFI_STATUS & 0x1) != 0x1);
	return WIFI_RX;
}

void sendstring_wifi(const char *string) {
    // putchar_wifi('\n');
    // WAIT_FOR_WIFI_READY

    int i;
    for (i = 0; string[i] != '\0'; i++) {
        putchar_wifi(string[i]);
    }

    /* Send line feed and carriage return */
    putchar_wifi('\n');
    putchar_wifi('\r');
}

void receivestring_wifi(char *buffer, int buffer_len, char start_char, char end_char) {
    buffer[0] = start_char;
    char char_received = 'a';
    int i;

    /* Wait for special command delimiter to start recording */
    for (i = 0; i < 100 && char_received != start_char; i++) {
        char_received = getchar_wifi();
    }

    for (i = 1; i < buffer_len && char_received != end_char; i++) {
        buffer[i] = char_received = getchar_wifi();
    }
    buffer[buffer_len-1] = '\0';
}
