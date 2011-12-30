#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cupl.h>

#define TBL_SIZE 2048

int main(int argc, char **argv) {
	int h = -1;

        if (argc < 2) {
                fprintf(stderr, "Usage: %s string\n", argv[0]);
                return 0;
        }

	h = cupl_hash_get(argv[1], strlen(argv[1]), TBL_SIZE);

	printf("hash: %d.\n", h);
	
	return 1;
}


