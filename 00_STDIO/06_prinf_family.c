#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("hello, world\n");

	fprintf(stderr, "hello, %s\n", "world");

	char buf[32];
	int year = 2020, month = 4, day = 6;
	sprintf(buf, "%d-%d-%d", year, month, day);
 	printf("%s\n", buf);
	
	char date[]="2020-04-06";
	printf("date = %d\n", atoi(date));

	return EXIT_SUCCESS;
}
