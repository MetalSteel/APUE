#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void* thread_cleanup(void *arg) {
    printf("%s\n", (char*)arg);
    return NULL;
}

static void* func(void *arg) {
    printf("thread is run...\n");

    pthread_cleanup_push(thread_cleanup, "cleanup 1");
    pthread_cleanup_push(thread_cleanup, "cleanup 2");
    pthread_cleanup_push(thread_cleanup, "cleanup 3");

    printf("registe cleanup over...\n");

    printf("thread is run other things...\n");
    
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);
    
    int *ret_val = malloc(sizeof(int));
    *ret_val = 10086;
    pthread_exit(ret_val);
//  return NULL;
}

int main(int argc, char *argv[]) {

    puts("Begin");

    pthread_t tid;

    int err = pthread_create(&tid, NULL, func, NULL);
    if(err != 0) {
        fprintf(stderr, "pthread_create(): %s\n", strerror(err));
        return EXIT_FAILURE;
    }
    
    int *ret_val;
    pthread_join(tid, (void**)&ret_val);
    printf("ret_val = %d\n", *ret_val);
    free(ret_val);

    puts("End");
    return EXIT_SUCCESS;
}
