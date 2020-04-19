#include <pthread.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THREAD_NUM 40
#define FILE_NAME "/tmp/out"

//static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx;

static void* add(void *arg) {
    FILE *fp = fopen(FILE_NAME, "r+");
    if(fp == NULL) {
        perror("fopen failed");
        pthread_exit(NULL);
    }
    
    char line_buf[1024];

    // lock
    pthread_mutex_lock(&mtx);

    fgets(line_buf, 1024, fp);
    sleep(1);
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", atoi(line_buf) + 1);
    fflush(fp);

    // unlock
    pthread_mutex_unlock(&mtx);

    fclose(fp);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    pthread_mutex_init(&mtx, NULL);

    pthread_t tid[THREAD_NUM];
    int err;

    for(int i = 0; i < THREAD_NUM; ++i) {
        err = pthread_create(tid + i, NULL, add, NULL);
        if(err != 0) {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            return EXIT_FAILURE;
        }
    }

    for(int i = 0; i < THREAD_NUM; ++i) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mtx);

    return EXIT_SUCCESS;
}
