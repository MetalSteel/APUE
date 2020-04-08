#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	if(argc < 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		exit(EXIT_SUCCESS);
	} 
	
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if(-1 == fd) {
		perror("open failed");
		exit(EXIT_SUCCESS);
	}
	
	// close STDOUT then set fd value is STDOUT_FILENO
	dup2(fd, STDOUT_FILENO);

	puts("Hello, World");
	
	return EXIT_SUCCESS;
}
