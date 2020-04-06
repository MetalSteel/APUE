#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv) {
	FILE *fp = fopen("tmp", "r");
	if(NULL == fp) {
		//fprintf(stderr, "fopen() failed! errno = %d\n", errno);
		//perror("fopen() failed");
		fprintf(stderr, "fopen() failed! errno = %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	puts("OK!");

	int ret = fclose(fp);
	if(ret == EOF) {
		perror("fclose() failed");
		exit(EXIT_FAILURE);
	}	

	return EXIT_SUCCESS;
}
