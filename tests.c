#include <string.h>
#include "tests.h"
#include "gps.h"
#include "wifi.h"
#include "data_package.h"


void test_gps() {
	printf("_____Starting GPS test_____\n");
	init_gps();

	struct gps_packet *gps_pkt = gps_packet_create();
	update_gps_data(gps_pkt);

    printf("packetStr: %s\n", gps_pkt->packetStr);
    printf("packetStr_copy: %s\n", gps_pkt->packetStr_copy);
    printf("utc_time: %s\n", gps_pkt->utc_time);
    printf("local_time: %s\n", gps_pkt->local_time);
    printf("latitude: %s\n", gps_pkt->latitude);
    printf("NS_indicator: %s\n", gps_pkt->NS_indicator);
    printf("longitude: %s\n", gps_pkt->longitude);
    printf("EW_indicator: %s\n", gps_pkt->EW_indicator);
    printf("satelites_used: %s\n", gps_pkt->satelites_used);
    printf("checksum: %s\n", gps_pkt->checksum);

	printf("_____Done GPS test_____\n");
}

void test_wifi() {
	printf("_____Starting wifi test_____\n");
	init_wifi();

	int buf_len = 500;
	char *buffer = malloc(sizeof(char)*buf_len);
	sendstring_wifi("print('hello world');");
	receivestring_wifi(buffer, buf_len, ';', '>');

	printf("Wifi Data: %s\n", buffer);
	free(buffer);

	printf("_____Done Wifi test_____\n");
}

void test_send_data_package() {
	printf("_____Starting send data_package test_____\n");
	init_gps();
	printf("GPS Initialized\n");
	init_wifi();
	printf("Wifi Initialized\n");

	struct data_package *data_pkg = pkg_create();
	struct gps_packet *gps_pkt = gps_packet_create();
	char *json_data = malloc(sizeof(char)*100);
	char *response = malloc(sizeof(char)*300);

	update_gps_data(gps_pkt);
	update_pkg(data_pkg, 5, 5, gps_pkt);

	printf("num_cars: %s\n", data_pkg->num_cars);
	printf("latitude: %s\n", data_pkg->latitude);
	printf("longitude: %s\n", data_pkg->longitude);
	printf("pst: %s\n", data_pkg->pst);
	printf("time_span: %s\n", data_pkg->time_span);

	pkg_to_command(data_pkg, json_data);
	printf("Command: %s\n", json_data);
	sendstring_wifi(json_data);
	printf("Command sent!\n");

	int i;
	for (i = 0; i < 300; i++) {
		response[i] = getchar_wifi();
		if (response[i] == '>') break;
	}

	printf("Wifi response: %s", response);
	free(json_data);

	printf("_____Done send data_package test_____\n");
}
