#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "altera_up_avalon_character_lcd.h"

char packetStr[82]; //Max length of message

char *utc_time;
char *latitude;
char *NS_indicator;
char *longitude;
char *EW_indicator;
char *satelites_used;
char *checksum;

void init_gps(void) {
	GPS_CONTROL = 0x15;
	GPS_BAUD = 0x7;
}

void gps_send_char(char c) {
	/* Wait until GPS is ready to receive next char */
	while ((GPS_STATUS & GPS_TX_MASK) != 0x2);
	GPS_TXDATA = c;
}

char gps_receive_char(void) {
	/* Wait until GPS has sent data */
	while ((GPS_STATUS & GPS_RX_MASK) != 0x1);
	return GPS_RXDATA;
}

/*
 * Store the packet recieved in an array
 */
void packet_to_str() {
	/* keep checking for chars until new packet is read */
	while (1) {
		char packet_char = gps_receive_char();
		/* Start of new packet */
		if(packet_char == '$'){
			int i = 0;
			/* Copy packet to array until <CR><LF> */
			while (packet_char != '\r'){
				/* Check that data is valid */
				if (packet_char != '\0') {
					packetStr[i] = packet_char;
					i++;
				}
				packet_char = gps_receive_char();
			}
			/* Append null to terminate the array */
			packetStr[i++] = '\0';
			break;
		}
	}
}

/*
 * Verify that the packet is of type GPGGA
 */
int check_GGA() {
	/* Check that the packet begins with GPGGA */
	return (packetStr[3] == 'G' && packetStr[4] == 'G' && packetStr[5] == 'A');
}

/*
 * Stores each element of GPS data in an array (Problem: sometimes no data for
 * a particular element, can't pass a NULL into an array..
 * loose uniformity of indices)
 */
void parse_packet(){
	/* total number of tokens in GPGGA packet - excluding <CR> */
	char **tokens[15];
	int i = 0;
	char *token = strtok(packetStr, ",");

	for (i = 0; token != NULL; i++) {
		tokens[i] = token;
		token = strtok (NULL, ",");
	}

	/* get tokens */
	utc_time = tokens[1]; //starts at 1 because 0 will be $GPGGA
	latitude = tokens[2];
	NS_indicator = tokens[3];
	longitude = tokens[4];
	EW_indicator = tokens[5];
	satelites_used = tokens [7];
	checksum = tokens[14];

	/* Shift commas left by two in lat and long */
	char upper = latitude[2];
	char lower = latitude[3];
	latitude[2] = '.';
	latitude[3] = upper;
	latitude[4] = lower;

	upper = longitude[3];
	lower = longitude[4];
	longitude[3] = '.';
	longitude[4] = upper;
	longitude[5] = lower;
}

/*
 * Covert UTC timestamp to local time
 */
void utc_to_local() {
	int hours_h = ((char)utc_time[0]) - '0';
	int hours_l = ((char)utc_time[1]) - '0';
	int minutes_h = ((char)utc_time[2]) - '0';
	int minutes_l = ((char)utc_time[3]) - '0';
	int seconds_h = ((char)utc_time[4]) - '0';
	int seconds_l = ((char)utc_time[5]) - '0';

	/* Add 8 hours to UTC time for Vancouver time */
	int hours = (hours_h*10 + hours_l + 4) % 24;

	hours_h = hours / 10;
	hours_l = hours % 10;
	printf("%d%d : %d%d : %d%d\n", hours_h, hours_l, minutes_h, minutes_l, seconds_h, seconds_l);

	/* Write the values to the hex displays */
	*HEX4_5 = (hours_h << 4) | hours_l;
	*HEX2_3 = (minutes_h << 4) | minutes_l;
	*HEX0_1 = (seconds_h << 4) | seconds_l;
}

void test_gps() {
	printf("Testing the GPS...\n");
	init_gps();
	printf("GPS successfully initalized\n");

	do {
		printf("Read next Packet\n");
		packet_to_str();
		printf("Packet contents: %s\n", packetStr);
	} while(!check_GGA());

	printf("A GGA packet was recieved.\n");
	parse_packet();
	utc_to_local();
	printf("Latitude: %s %s\n", latitude, NS_indicator);
	printf("Longitude: %s %s\n", longitude, EW_indicator);
}
