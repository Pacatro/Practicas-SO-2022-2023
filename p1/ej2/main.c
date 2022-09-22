#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){
    pid_t childpid, flag;
    int status;

    childpid = fork();

    switch(childpid){
        case -1:
            perror("ERROR, can`t create a child process");
            exit(EXIT_FAILURE);
        
        case 0:
            printf("I'm the child with ID: %d and my father has ID: %d\n", getpid(), getppid());
        break;

        default:
            sleep(10);
            while((flag == wait(&status)) > 0){
                if(WIFEXITED(status)){
                    printf("Child ID: %d finished, status = %d\n", flag, WEXITSTATUS(status));
                } else if(WIFSIGNALED(status)){
                    printf("\nChild ID: %d finished with signal %d\n\n", flag, WTERMSIG(status));
                }
            }   

            sleep(5);
            exit(EXIT_SUCCESS);

    }    
}