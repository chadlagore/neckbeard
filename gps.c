#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char packetStr[82]; //Max length of message

char *;
char *latitude;
char *NS_indicator;
char *longitude;
char *EW_indicator;
char *satelites_used;
char *checksum;

void init_gps(void) {
	GPS_CONTROL = 0x15;
	GPS_BAUD = 0x5;
}

void gps_send_char(char c) {
	/* Wait until GPS is ready to receive next char */
	while ((GPS_STATUS & GPS_TX_MASK) != 0x02);
	GPS_TXDATA = c;
}

char gps_receive_char(void) {
	/* Wait until GPS has sent data */
	while ((GPS_STATUS & GPS_RX_MASK) != 0x01);
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
}

/*
 * Covert UTC timestamp to local time
 */
void utc_to_local() {
	char *temp = ;
	int hours_h = (int) *temp;
	int hours_l = (int) *temp+1;
	int minutes_h = (int) *temp +2;
	int minutes_l = (int) *temp +3;
	int seconds_h = (int) *temp +4;
	int seconds_l = (int) *temp +5;

	/* Add 8 hours to UTC time for Vancouver time */
	int hours = (hours_h*10 + hours_l + 8) % 24;

	hours_h = hours / 10;
	hours_l = hours % 10;
	printf("%d%d:%d%d:%d%d\n", hours_h, hours_l, minutes_h, minutes_l, seconds_h, seconds_l);
}

void test_gps() {
	printf("Testing the GPS...\n");
	init_gps();
	printf("GPS successfully initalized\n");

	do {
		printf("Read next Packet\n");
		packet_to_str();
	} while(!check_GGA());

	printf("A GGA packet was recieved.\n");
	parse_packet();
	utc_to_local();
	printf("Latitude: %s %s\n", latitude, NS_indicator);
	printf("Longitude: %s %s\n", longitude, EW_indicator);
}

/* Functions for Data Logger
int swap_endian(char *s){
register int val;
val = strtoul(s, NULL, 16) ; // convert to 4 byte int form in base 16
val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
val = (val << 16) | ((val >> 16) & 0xFFFF);
return val ;
}

float convert_latitude(int x){
static char buff[100] ;
float *ptr = (float *)(&x) ; // cast int to float
float f = *ptr ; // get the float
sprintf(buff, "%2.4f", f); // write in string to an array
return buff ;
}

float convert_longitude(int x){
static char buff[100] ;
float *ptr = (float *)(&x) ;
float f = *ptr ;
sprintf(buff, "%3.4f", f);
return buff ;
}
*/
