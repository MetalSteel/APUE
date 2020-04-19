#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THREAD_NUM 4

static pthread_mutex_t mtx[THREAD_NUM];

typedef struct pthread_arg {
    char ch;
} pthread_arg;

static int next(int num) {
    return ++num >= THREAD_NUM ? 0 : num;
}

static void* write_console(void *arg) {
    char ch = ((pthread_arg*)arg)->ch;
    int num = ch - 'a';

    while(1) {
        pthread_mutex_lock(mtx + num);
        write(STDOUT_FILENO, &ch, 1);
        pthread_mutex_unlock(mtx + next(num));
    }

    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    int err;
    static pthread_t tid[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; ++i) {
        pthread_mutex_init(mtx + i, NULL);
        pthread_mutex_lock(mtx + i);
        pthread_arg *arg = malloc(sizeof(pthread_arg));
        arg->ch = 'a' + i;
        err = pthread_create(tid + i, NULL, write_console, arg); 
        if(err != 0) {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            return EXIT_FAILURE;
        }
    }

    pthread_mutex_unlock(mtx);
    
    alarm(5);

    for(int i = 0; i < THREAD_NUM; ++i) {
        pthread_join(tid[i], NULL);
    }
    printf("alarm exec...\n");

    return EXIT_SUCCESS;
}
