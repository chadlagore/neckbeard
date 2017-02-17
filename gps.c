#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

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
 * Create a gps packet to store data from the GPS
 */
struct gps_packet *gps_packet_create() {
	struct gps_packet *packet = malloc(sizeof(struct gps_packet));
	packet->packetStr = malloc(sizeof(char)*MAX_PACKET_LENGTH);
	packet->packetStr_copy = malloc(sizeof(char)*MAX_PACKET_LENGTH);
	packet->local_time = malloc(sizeof(char)*9);

	return packet;
}


void gps_packet_destroy(struct gps_packet *pkt) {
	free(pkt->packetStr);
	free(pkt->packetStr_copy);
	free(pkt->local_time);
	free(pkt);
}


/*
 * Store the packet recieved in pack->packetStr
 */
void receive_packet(struct gps_packet *pkt) {
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
					pkt->packetStr[i] = packet_char;
					i++;
				}
				packet_char = gps_receive_char();
			}
			/* Append null to terminate the array */
			pkt->packetStr[i] = '\0';
			break;
		}
	}
}


/*
 * Verify that the packet is of type GPGGA
 */
int is_GGA(struct gps_packet *pkt) {
	/* Check that the packet begins with GPGGA */
	return (pkt->packetStr[3] == 'G'
		&& pkt->packetStr[4] == 'G'
		&& pkt->packetStr[5] == 'A');
}


/*
 * Stores each element of GPS data in an array (Problem: sometimes no data for
 * a particular element, can't pass a NULL into an array..
 * loose uniformity of indices)
 */
void parse_packet(struct gps_packet *pkt) {
	sprintf(pkt->packetStr_copy, "%s", pkt->packetStr);

	char **tokens[15];
	int i = 0;
	char *token = strtok(pkt->packetStr_copy, ",");

	for (i = 0; token != NULL; i++) {
		tokens[i] = token;
		token = strtok (NULL, ",");
	}

	/* get tokens */
	pkt->utc_time = tokens[1]; //starts at 1 because 0 will be $GPGGA
	pkt->latitude = tokens[2];
	pkt->NS_indicator = tokens[3];
	pkt->longitude = tokens[4];
	pkt->EW_indicator = tokens[5];
	pkt->satelites_used = tokens[7];
	pkt->checksum = tokens[14];

	/* Shift commas left by two in lat and long */
    char upper = pkt->latitude[2];
    char lower = pkt->latitude[3];
    pkt->latitude[2] = '.';
    pkt->latitude[3] = upper;
    pkt->latitude[4] = lower;

    upper = pkt->longitude[3];
    lower = pkt->longitude[4];
    pkt->longitude[3] = '.';
    pkt->longitude[4] = upper;
    pkt->longitude[5] = lower;
}


/*
 * Covert UTC timestamp to local time and return it
 * in string format
 */
char *utc_to_local(struct gps_packet *pkt) {
	int hours_h = ((char) pkt->utc_time[0] - '0');
	int hours_l = ((char) pkt->utc_time[1] - '0');
	int minutes_h = ((char) pkt->utc_time[2] - '0');
	int minutes_l = ((char) pkt->utc_time[3] - '0');
	int seconds_h = ((char) pkt->utc_time[4] - '0');
	int seconds_l = ((char) pkt->utc_time[5] - '0');

	/* Add 8 hours to UTC time for Vancouver time */
	int hours = (hours_h*10 + hours_l + 16) % 24;
	hours_h = hours / 10;
	hours_l = hours % 10;

	/* Write the values to the hex displays */
	// *HEX4_5 = (hours_h << 4) | hours_l;
	// *HEX2_3 = (minutes_h << 4) | minutes_l;
	// *HEX0_1 = (seconds_h << 4) | seconds_l;

	sprintf(pkt->local_time, "%d%d:%d%d:%d%d\0", hours_h, hours_l, minutes_h, minutes_l, seconds_h, seconds_l);
	return pkt->local_time;
}

void update_gps_data(struct gps_packet *pkt) {
	do {
		receive_packet(pkt);
	} while(!is_GGA(pkt));
	parse_packet(pkt);
	utc_to_local(pkt);
}
