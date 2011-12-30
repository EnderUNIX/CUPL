#include <stdio.h>
#include <stdlib.h>
#include <cupl.h>

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s string pattern\n", argv[0]);
		fprintf(stderr, "       %s \"Some girls are walking\" \"^[Ss]ome\"\n", argv[0]);
		return 0;
	}

	if (cupl_match_regex(argv[1], argv[2]) == 1)
		printf("String \"%s\" matched the pattern \"%s\".\n", argv[1], argv[2]);
	else
		printf("String \"%s\" didn't match the pattern \"%s\".\n", argv[1], argv[2]);

	return 1;
}


