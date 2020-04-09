#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

static off_t file_length(const char *file_name) {
	struct stat file_stat;
	int ret = stat(file_name, &file_stat);

	if(-1 == ret) {
		perror("stat failed");
		exit(EXIT_FAILURE);
	}

	return file_stat.st_size;
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	printf("%s length: %lld\n", argv[0], file_length(argv[1]));

	return EXIT_SUCCESS;
}
