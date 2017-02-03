#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

	return packet;
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
	/* total number of tokens in GPGGA packet - excluding <CR> */
	char **tokens[15];
	int i = 0;
	char *token = strtok(pkt->packetStr, ",");

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
}

/*
 * Covert UTC timestamp to local time and return it
 * in string format
 */
char *utc_to_local(struct gps_packet *pkt) {
	char *temp = pkt->utc_time;
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

	/* Write the values to the hex displays */
	*HEX4_5 = (hours_h << 4) | hours_l;
	*HEX2_3 = (minutes_h << 4) | minutes_l;
	*HEX0_1 = (seconds_h << 4) | seconds_l;

	sprintf(pkt->local_time, "%d%d:%d%d:%d%d", hours_h, hours_l, minutes_h, minutes_l, seconds_h, seconds_l);
	return pkt->local_time;
}

void udpate_gps_data(struct gps_packet *pkt) {
	do {
		receive_packet(pkt);
		printf("Packet str: %s\n", pkt->packetStr);
	} while(!is_GGA(pkt));
	printf("Parsing packet\n");
	parse_packet(pkt);
	utc_to_local(pkt);
}
