#include <stdlib.h>
#include "package.h"

/*
 * Initializes a package and returns a pointer to it
 * Caller is responsible for calling pkg_destroy when
 * done with this package
 */
struct package *pkg_create() {
	struct package *pkg = malloc(sizeof(struct package));
	pkg->PST = malloc(sizeof(char)*8);
	return pkg;
}

/*
 * Frees memory allocated by pkg struct and its constituents
 */
struct package *pkg_destroy(struct package *pkg) {
	free(pkg->PST);
	free(pkg);
}

/*
 * Convert the package to a JSON string
 * Caller is responsible for calling free() on string
 * returned by this funciton when done with it
 */
char *pkg_to_json(struct package *pkg) {
	char *json_str = malloc(sizeof(char)*100);
	char *base_str = "{\"num_cars\" :1, \"latitude\" :2, \"longitude\" :3, \"PST\" :4, \"time_span\" :5 }\0";

	/* Fill in values in the base JSON string using package data */
	int i;
	for (i = 0; base_str[i] != '\0'; i++) {
		/* If we are not looking at a colon just copy it to the JSON string */
		if (base_str[i] != ':') {
			json_str[i] = base_str[i];
		}
		/* Otherwise we need to insert the data */
		else {
			char marker = base_str[++i];
			json_str[i++] = ' ';

			/* Copy time span */
			if (marker == '5') {
				sprintf(json_strj + i, "%d", pkg->time_span);
			}

			/* Copy PST */
			else if (marker == '4') {
				sprintf(json_strj + i, "%s", pkg->PST);
			}

			/* Copy longitude */
			else if (marker == '3') {
				sprintf(json_strj + i, "%d", pkg->longitude);
			}

			/* Copy latitude */
			else if (marker == '2') {
				sprintf(json_strj + i, "%d", pkg->latitude);
			}

			/* Copy num_cars */
			else {
				sprintf(json_strj + i, "%d", pkg->num_cars);
			}
		}
	}
	return json_str;
}
