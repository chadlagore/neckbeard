#ifndef _PACKAGE_H_
#define _PACKAGE_H_

/*
 * A package containing data to be sent to the server
 * num_cars: the number of cars that have passed since the last
 				  packet was sent
 * latitude: the device's latitude
 * longitude: the device's longitude
 * pst: the pacific standard time at which this package was sent
 * time_span: the number of seconds over whidh the data in this package was collected
 */
struct package {
	int num_cars;
	char *latitude;
	char *longitude;
	char *pst;
	int time_span;
};

struct package *pkg_create(void);
void pkg_destroy(struct package *pkg);
char *pkg_to_json(struct package *pkg);

#endif /* _PACKAGE_H_ */
