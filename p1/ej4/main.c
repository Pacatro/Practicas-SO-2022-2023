#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "functions.h"

int main(int argc, char **argv){
    if(argc != 3){
        perror("ERROR, YOU MUST WRITE TWO NUMBERS IN THE COMMAND LINE (./main.c x y)");
        exit(EXIT_FAILURE);
    }

    pid_t childpid, flag;
    int status, i;

    for(i = 1; i <= 2; i++){
        childpid = fork();

        switch(childpid){
            case -1:
                perror("ERROR, CAN'T CREATE CHILD PROCESS, ");
                printf("errno = %d\n", errno);
            exit(EXIT_FAILURE);

            case 0:
                if(i == 1){
                    printf("\nI'm the child number %d, PID: %d, PPID: %d Calculating %s!...\n", i, getpid(), getppid(), argv[1]);
                    child1(argv);
                }
                
                sleep(1);

                if(i == 2){
                    printf("\nI'm the child number %d, PID: %d, PPID: %d Calculating %s!...\n", i, getpid(), getppid(), argv[2]);
                    child2(argv);
                }

            break;

            default:
                while((flag = wait(&status)) > 0){
                    if(WIFEXITED(status)){
                        printf("\nFather PID: %d, child with PID %d finished, status = %d\n", getpid(), childpid, WEXITSTATUS(status));
                    }

                    else if(WIFSIGNALED(status)){
                        printf("Father PID: %d, child with PID %d finished at recibe signal, status = %d\n", getpid(), childpid, WTERMSIG(status));
                    }
                }

                if(flag = (pid_t)-1 && errno == ECHILD){
                    printf("Process %d, no more childs to wait, errno = %d -> %s\n", getpid(), errno, strerror(errno));
                } else{
                    printf("ERROR. CAN'T INVOQUE wait() or waitpid(), errno = %d -> %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }
        }
    }

    printf("\nEND OF PROGRAM.\n");
    exit(EXIT_SUCCESS);

}