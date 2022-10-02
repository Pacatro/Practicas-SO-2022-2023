#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void message(int signal){
    alarm(1);
    pause();
    printf("I recibe the message!\n");
    printf("SIGNAL VALUE = %d", signal);
    return;
}

int main(){
    pid_t childpid, flag;
    int status;

    childpid = fork();
    switch(childpid){
        case -1:
            perror("Can't create child.");
            printf("errno value = %d", errno);
            exit(EXIT_FAILURE);
        break;

        case 0:
            printf("I'm the child, PID: %d, PPID: %d\n", getpid(), getppid());
            if(signal(SIGUSR1, message) == SIG_ERR){
                perror("Signal error");
                printf("errno value = %d", errno);
                exit(EXIT_FAILURE);
            }

        break;

        default:
            printf("I'm the father, PID: %d\n", getpid());

            while((flag = wait(&status)) > 0){
                if(WIFEXITED(status)){
                    printf("\nFather PID: %d, child with PID %d fiished, status = %d\n", getpid(), childpid, WEXITSTATUS(status));
                }

                else if(WIFSIGNALED(status)){
                    printf("Father PID: %d, child with PID %d finished at recibe signal, status = %d\n", getpid(), childpid, WTERMSIG(status));
                }
            }

            if(flag == (pid_t)-1 && errno == ECHILD){
                printf("Process %d, no more childs to wait, errno = %d -> %s\n", getpid(), errno, strerror(errno));
            } else{
                printf("ERROR. CAN'T INVOQUE wait() or waitpid(), errno = %d -> %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }

        break;
    }

    exit(EXIT_SUCCESS);
}