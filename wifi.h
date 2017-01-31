#ifndef _WIFI_H_
#define _WIFI_H_

#define WIFI_CONTROL     (*(volatile unsigned char *)(0x84000240))
#define WIFI_STATUS      (*(volatile unsigned char *)(0x84000240))
#define WIFI_TX          (*(volatile unsigned char *)(0x84000242))
#define WIFI_RX          (*(volatile unsigned char *)(0x84000242))
#define WIFI_BAUD        (*(volatile unsigned char *)(0x84000244))

/* Set baud rate to 115k */
void init_wifi(void);

/* Send character to wifi */
void putchar_wifi(int c);

/* Recieve character from wifi */
int getchar_wifi(void);

/* Send string to wifi (string must be '\0' terminated) */
void sendstring_wifi(const char *string);

#endif /* _WIFI_H_ */
