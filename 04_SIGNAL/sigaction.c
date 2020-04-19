#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

void exit_handler(int signum, siginfo_t *info, void *ucontext) {
    if(info->si_code == SI_KERNEL)
        return;
    printf("xixi\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    sa.sa_sigaction = exit_handler; 
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGQUIT);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
   
    pause();

    return EXIT_SUCCESS;
}
