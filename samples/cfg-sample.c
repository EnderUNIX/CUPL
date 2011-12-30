#include <stdio.h>
#include <stdlib.h>
#include <cupl.h>

int main(int argc, char **argv) {
	cfg_data *cfg;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s config\n", argv[0]);
		return 0;
	}

	/* Init parser and get a cfg data pointer. */
	if ((cfg = cupl_init_cfg(argv[1])) == NULL) {
		fprintf(stderr, "Error in init_config_parser!\n");
		return -1;
	}

	/* Print info about the library. */
	cupl_print_info(cfg);

	/* Print parsed items. */
	cupl_print_items(cfg);

	printf("Listen address is %s.\n", cupl_get_var("ListenAddress", cfg));

	/* Close config file and free cfg data object. */
	cupl_release_cfg(cfg);

	return 1;
}


