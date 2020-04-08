#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buf[] = {'b'};
	
	putchar('a');
	write(1, buf, 1);
	
	putchar('a');
	write(1, buf, 1);
	
	putchar('a');
	write(1, buf, 1);
	// can use strace cmd to trace system call
	// output result is: bbbaaa

	return EXIT_SUCCESS;
}

