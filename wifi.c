#include "wifi.h"

void init_wifi() {
    WIFI_CONTROL = 0x15;
    WIFI_BAUD = 0x01;

    /* Send 10 carriage returns and line feeds */
    int i;
    for (i = 0; i < 10; i++) sendstring_wifi("\n\r");
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
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        putchar_wifi(string[i]);
    }

    /* Send carriage return and line feed */
    putchar_wifi('\n');
    putchar_wifi('\r');
}

void receivestring_wifi(char *buffer, int buffer_len, char start_char, char end_char) {
    char char_received = 'a';
    int i;

    /* Wait for special command delimiter to start recording */
    while (getchar_wifi() != start_char);

    for (i = 0; i < buffer_len && char_received != end_char; i++) {
        buffer[i] = char_received = getchar_wifi();
    }

    buffer[i] = '\0';
}
