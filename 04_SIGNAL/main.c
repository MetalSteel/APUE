#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void int_handler(int signum) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("!");
}

int main(int argc, char *argv[]) {
    signal(SIGINT, int_handler);

    sigset_t set, oset, saveset;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    
    sigprocmask(SIG_UNBLOCK, &set, &saveset);
    sigprocmask(SIG_BLOCK, &set, &oset);
   
    while(1) {
        
        for(int i = 0; i < 5; ++i) {
            setvbuf(stdout, NULL, _IONBF, 0);
            printf("*");
            sleep(1);
        }
        
        printf("\n");
        sigsuspend(&oset);
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);

    return EXIT_SUCCESS;
}
