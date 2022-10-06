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

    kill(process_pid, SIGUSR1);

    sleep(1);

    kill(process_pid, SIGKILL);

    exit(EXIT_SUCCESS);
}