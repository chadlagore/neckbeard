#ifndef _WIFI_H_
#define _WIFI_H_

#define WIFI_CONTROL     (*(volatile unsigned char *)(0x84000240))
#define WIFI_STATUS      (*(volatile unsigned char *)(0x84000240))
#define WIFI_TX          (*(volatile unsigned char *)(0x84000242))
#define WIFI_RX          (*(volatile unsigned char *)(0x84000242))
#define WIFI_BAUD        (*(volatile unsigned char *)(0x84000244))

/* This must be called before commands can be sent to the wifi chip */
#define WAIT_FOR_WIFI_READY   while (getchar_wifi() != '>');

/* Set baud rate to 115k */
void init_wifi(void);

/* Send character to wifi */
void putchar_wifi(char c);

/* Recieve character from wifi */
char getchar_wifi(void);

/* Send string to wifi (string must be '\0' terminated) */
void sendstring_wifi(const char *string);

/*
 * Fill to_fill with wifi output up to its buffer_len
 * only copies in data after the delimiter
 */
void receivestring_wifi(char *buffer, int buffer_len, char start_char, char end_char);

#endif /* _WIFI_H_ */
