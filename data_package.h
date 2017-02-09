#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include "gps.h"

/*
 * A package containing data to be sent to the server
 * num_cars: the number of cars that have passed since the last
 				  packet was sent
 * latitude: the device's latitude
 * longitude: the device's longitude
 * pst: the pacific standard time at which this package was sent
 * time_span: the number of seconds over whidh the data in this package was collected
 */
struct data_package {
	char *num_cars;
	char *latitude;
	char *longitude;
	char *pst;
	char *time_span;
};

struct data_package *pkg_create(void);
void pkg_destroy(struct data_package *pkg);
void pkg_to_command(struct data_package *pkg, char *json_str);
void update_pkg(struct data_package *data_pkg, int num_cars, int time_span, struct gps_packet *gps_pkt);

#endif /* _PACKAGE_H_ */
