#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *tmp = tmpfile();
	// tmpnam is not thread safe!!! so you can use tmpfile function
	fprintf(tmp, "hello,%s", "world");
	rewind(tmp);
	
	char buf[32] = {0};
	fscanf(tmp, "%s", buf);
	printf("buf = %s\n", buf);	

	fclose(tmp);
	
	return EXIT_SUCCESS;
}
