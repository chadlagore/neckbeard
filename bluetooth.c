#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bluetooth.h"


void init_bluetooth(void){
	BLUETOOTH_CONTROL = 0x15;
	BLUETOOTH_BAUD = 0x01; //datasheet recommends 115k baud rate
}

void send_ch(char c){
    while ((BLUETOOTH_STATUS & BLUETOOTH_TX_MASK) != 0x02);
    BLUETOOTH_TXDATA = c;
}

void send_string(char str[]){
    int i;
	int length = strlen(str);

    for (i = 0; i < length; i++) {
        usleep(100000); //100ms wait
		send_char(str[i]);
	}
}

void command_mode(void){
    printf("Entering Command Mode...\n");
	usleep(1000000); // 1s wait
	send_string("$$$");
	usleep(1000000);
}

void data_mode(void) {
    printf("Entering Data Mode...\n");
	usleep(1000000); // 1s wait
	send_string("---\r\n");
	usleep(1000000);
}

void reset_bluetooth(void) {
	command_mode();
	send_string("SF,");
	send_string("1\r\n");
	data_mode();
}

void set_name(char name[]) {
	command_mode();
	send_string("SN,");
	send_string(name);
	send_string("\r\n");
	data_mode();
}

void set_pw(char pw[]) {
	command_mode();
	send_string("SP,");
	send_string(pw);
	send_string("\r\n");
	data_mode();
}

void test(void) {
    printf("Testing Bluetooth...\n");
    init_bluetooth();
    printf("Connection established...\n");

    char btname[] = "sexysamharris";
    char password[] = "morning";

    set_name(btname);
    set_pw(password);

    printf("Bluetooth successfully updated!\n");
}
