#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void message(int signal){
    printf("I recibe the signal!\n");
    printf("My PID is: %d\n", getpid());   
    printf("Signal = %d\n\n", signal);
}

int main(){

    if(signal(SIGUSR1, message) == SIG_ERR){
        perror("Signal error");
        printf("Errno = %d", errno);
        exit(EXIT_FAILURE);
    }

    
    while(1){
        pause();
    }
    

    exit(EXIT_SUCCESS);
}