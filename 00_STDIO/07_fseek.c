#include <stdio.h>
#include <stdlib.h>

// fseeko and ftello replace fseek and ftell
// but fseeko/ftello is POSIX/SUS Standard not C89/C99 Standard
int main(int argc, char *argv[]) {
	FILE *fp = fopen("mine", "w+");

	fprintf(fp, "hello, %s", "world");
	printf("mine file file pointer %d\n", ftell(fp));	
	fflush(fp);
	
	//fseek(fp, 0, SEEK_SET);
	rewind(fp);
	printf("mine file file pointer %d\n", ftell(fp));	

	char buf[32] = {0};
	fgets(buf, 32, fp);
	printf("%s\n", buf);	

	fclose(fp);
	
	return EXIT_SUCCESS;
}
