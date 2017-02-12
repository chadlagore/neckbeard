#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data_package.h"

/*
 * Initializes a data_package and returns a pointer to it
 * Caller is responsible for calling pkg_destroy when
 * done with this data_package
 */
struct data_package *pkg_create() {
	struct data_package *pkg = malloc(sizeof(struct data_package));
	pkg->pst = malloc(sizeof(char)*8);
	pkg->num_cars = malloc(sizeof(char)*8);
	pkg->latitude = malloc(sizeof(char)*8);
	pkg->longitude = malloc(sizeof(char)*8);
	pkg->time_span = malloc(sizeof(char)*8);
	return pkg;
}

/*
 * Frees memory allocated by pkg struct and its constituents
 */
void pkg_destroy(struct data_package *pkg) {
	free(pkg->pst);
	free(pkg);
}

/*
 * Convert the data_package to a JSON string and store it in json_str
 */
void pkg_to_command(struct data_package *pkg, char *json_str) {
	strcpy(json_str, "check_wifi('");
	strcat(json_str, "{\"num_cars\" : ");
	strcat(json_str, pkg->num_cars);
	strcat(json_str, ", \"latitude\" : ");
	strcat(json_str, pkg->latitude);
	strcat(json_str, ", \"longitude\" : ");
	strcat(json_str, pkg->longitude);
	strcat(json_str, ", \"pst\" : ");
	strcat(json_str, pkg->pst);
	strcat(json_str, ", \"time_span\" : ");
	strcat(json_str, pkg->time_span);
	strcat(json_str, "}')\0");
}

/*
 * Fill contents of this data package with data from gps packet
 */
void update_pkg(struct data_package *data_pkg, int num_cars, int time_span, struct gps_packet *gps_pkt) {
	strcpy(data_pkg->num_cars, gps_pkt->latitude);
	strcpy(data_pkg->latitude, gps_pkt->latitude);
	strcpy(data_pkg->longitude, gps_pkt->longitude);
	strcpy(data_pkg->pst, gps_pkt->local_time);
	strcpy(data_pkg->time_span, gps_pkt->latitude);
}
