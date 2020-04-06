#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv) {
	FILE *fp = NULL;
	int count = 0;

	while(1) {
		fp = fopen("tmp", "w");
		if(NULL == fp) {
			perror("fopen() failed");
			break;
		}
		count++;
	}		
	
	printf("count = %d\n", count);
	
	return EXIT_SUCCESS;
}
