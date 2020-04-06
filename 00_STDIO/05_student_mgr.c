#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
	unsigned no;
	char name[32];
	unsigned age;
	unsigned grade;
}Student;

int main(int argc, char *argv[]) {
	/*
	Student stus[3] = {
		{1, "wanggang", 24, 100},
		{2, "wanghao", 24, 60},
		{3, "wangwenqiang", 25, 90}
	};
		
	FILE *fp = fopen("tmp", "w");
	if(NULL == fp) {
		perror("fopen() failed");
		exit(EXIT_FAILURE);
	}
	
	size_t sz = fwrite(stus, sizeof(Student), 3, fp);	
	printf("write %d item\n", sz);
	*/

	Student stus[3];

	FILE *fp = fopen("tmp", "r");
	if(NULL == fp) {
		perror("fopen failed");
		exit(EXIT_FAILURE);
	}	
	
	size_t num = fread(stus, sizeof(stus), 3, fp);
	printf("read %d item\n", num);	
	
	for(int i = 0; i < 3; ++i) {
		printf("%u %s %u %u\n", stus[i].no, stus[i].name, stus[i].age, stus[i].grade);
	}

	fclose(fp);	

	return EXIT_SUCCESS;
}
