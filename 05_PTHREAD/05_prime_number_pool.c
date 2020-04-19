#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT  30000000
#define RIGHT 30000200
#define NUM   4

static int num = 0;
static pthread_mutex_t mtx_num;

static void* calc_prime(void *arg) {
    int val = 0;

    while(1) {
        pthread_mutex_lock(&mtx_num);
        while(num == 0) {
            pthread_mutex_unlock(&mtx_num);
            sched_yield();
            pthread_mutex_lock(&mtx_num);
        }

        if(num == -1) {
            pthread_mutex_unlock(&mtx_num);
            break;
        }

        val = num;
        num = 0;
        pthread_mutex_unlock(&mtx_num);

        int flag = 0;
        for(int i = 2; i < val; ++i) {
            if(val % i == 0) {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            printf("[%ld] %d is prime\n", pthread_self(), val);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t tid[NUM];
    int err;
    
    for(int i = 0; i < NUM; ++i) {
        err = pthread_create(tid + i, NULL, calc_prime, NULL);
        if(err != 0) {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            return EXIT_FAILURE;
        }
    }

    for(int i = LEFT; i <= RIGHT; ++i) {
        pthread_mutex_lock(&mtx_num);

        while(num != 0) {
            pthread_mutex_unlock(&mtx_num);
            sched_yield();
            pthread_mutex_lock(&mtx_num);
        }

        num = i;
        pthread_mutex_unlock(&mtx_num);
    }

    pthread_mutex_lock(&mtx_num);
    while(num != 0) {
        pthread_mutex_unlock(&mtx_num);
        sched_yield();
        pthread_mutex_lock(&mtx_num);
    }
    num = -1;
    pthread_mutex_unlock(&mtx_num);

    for(int i = 0; i < NUM; ++i) {
        pthread_join(tid[i], NULL);
    }

    return EXIT_SUCCESS;
}
