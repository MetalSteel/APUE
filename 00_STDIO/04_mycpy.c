#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 32

int main(int argc, char *argv[]) {
	if(argc < 3) {
		fprintf(stderr, "Usage: %s <src_filename> <dest_filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *src_fp = fopen(argv[1], "r");
	if(NULL == src_fp) {
		perror("fopen() failed");
		exit(EXIT_FAILURE);
	}	
	
	FILE *dst_fp = fopen(argv[2], "w");
	if(NULL == dst_fp) {
		fclose(src_fp);
		perror("fopen() failed");
		exit(EXIT_FAILURE);
	}	
	
	char buf[BUFSIZE] = {0};
	while(NULL != fgets(buf, BUFSIZE, src_fp)) {
		fputs(buf, dst_fp);
	}

	fclose(dst_fp);
	fclose(src_fp);

	return EXIT_SUCCESS;
}
