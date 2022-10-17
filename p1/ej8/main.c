#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

    if(argc != 2){
        perror("Command line error");
        printf("You must write the pid of the other process (./ej8.exe <pid>)");
        exit(EXIT_FAILURE);
    }

    pid_t process_pid = atoi(argv[1]);

    printf("Sending signal...\n");
    if(kill(process_pid, SIGUSR1) == -1){
        perror("Signal error");
        printf("Can't send signal, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    sleep(1);

    printf("Killing process...\n");
    if(kill(process_pid, SIGKILL) == -1){
        perror("Signal error");
        printf("Can't send signal, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}