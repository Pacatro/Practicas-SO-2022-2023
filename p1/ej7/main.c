#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void message(int signal){
    printf("\tI recibe the signal!\n");
    printf("\tSignal = %d\n\n", signal);
}

int main(){
    pid_t childpid, flag;
    int status, message_cont = 0;

    childpid = fork();
    switch(childpid){
        case -1:
            perror("Can't create child.");
            printf("errno value = %d", errno);
            exit(EXIT_FAILURE);
        break;

        case 0:

            if(signal(SIGUSR1, message) == SIG_ERR){
                perror("Signal error");
                exit(EXIT_FAILURE);
            }

            while(1){
                pause();
            }
        
        break;

        default:
            printf("I'm the father, PID: %d\n\n", getpid());

            for(message_cont = 0; message_cont < 5; message_cont++){
                kill(childpid, SIGUSR1);
                printf("%d\n", message_cont);
                sleep(1);
            }
            
            kill(childpid, SIGKILL);

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