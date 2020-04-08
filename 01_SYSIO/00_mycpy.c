#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BUFSIZE is stack memory, so you didn't too large!!!(ulimit -a)
#define BUFSIZE 1024 * 8

int main(int argc, char *argv[]) {
	// program usage
	if(argc < 3) {
		printf("Usage: %s <filename> <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// open input file
	int src_fd = open(argv[1], O_RDONLY);
	if(-1 == src_fd) {
		perror("open argv[1] failed");
		exit(EXIT_FAILURE);
	}

	// open output file
	int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(-1 == dst_fd) {
		perror("open argv[2] failed");
		exit(EXIT_FAILURE);
	}
	
	// read write related variable
	char buf[BUFSIZE] = {0};
	int len = 0;

	// read from file and write to output file
	while(1) {
		// read from input file
		len = read(src_fd, buf, BUFSIZE);
		
		// check is read error
		if(-1 == len) {
			perror("read failed");
			break;
		}
		
		// check is read eof
		if(0 == len) {
			break;
		}
		
		// confirm buf is write output file
		int ret = 0;
		int pos = 0;
		while(len > 0) {
			// write to output file
			ret = write(dst_fd, buf + pos, len);
			
			// check is write error
			if(-1 == ret) {
				perror("write failed");
				goto close_file;
			}
			
			// modify write related variable
			pos += ret;
			len -= ret;
		}
	}

	// close file
close_file:
	if(-1 == close(dst_fd)) {
		perror("close dst fd failed");
		exit(EXIT_FAILURE);
	}
	
	if(-1 == close(src_fd)) {
		perror("close src fd failed");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

