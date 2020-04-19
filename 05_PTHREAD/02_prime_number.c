#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT  30000000
#define RIGHT 30000400
#define NUM   (RIGHT - LEFT + 1)

typedef struct pthread_arg {
    int num;
} pthread_arg;

static void* calc_prime(void *arg) {
    int num = ((pthread_arg*)arg)->num;

    int flag = 0;
    for(int i = 2; i < num; ++i) {
        if(num % i == 0) {
            flag = 1;
            break;
        }
    }
    
    if(flag == 0)
        printf("%d is prime\n", num);

    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    pthread_t tid[NUM];
    int err;
    
    for(int i = LEFT; i <= RIGHT; ++i) {
        pthread_arg *arg = malloc(sizeof(pthread_arg));
        if(arg == NULL) {
            perror("malloc() failed");
            return EXIT_FAILURE;
        }
        
        arg->num = i;

        err = pthread_create(&tid[i - LEFT], NULL, calc_prime, arg);
        if(err != 0) {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            return EXIT_FAILURE;
        }
    }

    void *ret_ptr;
    for(int i = LEFT; i <= RIGHT; ++i) {
        pthread_join(tid[i - LEFT], &ret_ptr);
        free(ret_ptr);
    }

    return EXIT_SUCCESS;
}
