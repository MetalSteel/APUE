#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

//size_t getline(char **lineptr, size_t *n, FILE *stream);

int main(int argc, char *argv[]) {
	FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("./08_getline.c", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu, malloc length %zu :", read, len);
        printf("%s", line);
    }

    free(line);

	return EXIT_SUCCESS;
}
