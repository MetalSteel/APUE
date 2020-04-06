#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");
	if(NULL == fp) {
		perror("fopen() failed");
		exit(EXIT_FAILURE);
	} 
	
	unsigned int count = 0;
	while(EOF != fgetc(fp)) {
		count++;
	}

	printf("%s has %u characters\n", argv[1], count);

	return EXIT_SUCCESS;
}
