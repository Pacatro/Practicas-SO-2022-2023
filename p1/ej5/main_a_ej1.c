#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int var = 0;

int main(int argc, char **argv){

    int nProcess, status, i;
    pid_t chilpid = 1, flag;

    if(argc != 2){
        perror("You must write the number of process ($ ./main_a.c 5)");
        exit(EXIT_FAILURE);
    }

    nProcess = atoi(argv[1]);

    printf("Number of process created: %d\n\n", nProcess);

    for(i = 1; i <= nProcess && chilpid != 0; i++){
        chilpid = fork();

        switch(chilpid){
            case -1:
                perror("\nCan't create child\n");
                exit(EXIT_FAILURE);

            case 0:
                printf("I'm the child number %d, with pid: %d and my father is %d\n\n", i, getpid(), getppid());
                var+=1;
            exit(EXIT_SUCCESS);
        }
    }

    
    while((flag = wait(&status)) > 0){
        if(WIFEXITED(status)){
            printf("Child ID: %d finished, status = %d\n", flag, WEXITSTATUS(status));
        }

        else if(WIFSIGNALED(status)){
            printf("\nChild ID: %d finished with signal %d\n\n", flag, WTERMSIG(status));
        }
    }

    if(flag == -1 && errno == ECHILD){
        printf("\n");
        printf("Parent process %d, there aren no more childs to wait. errno = %d, defined as: %s\n", getpid(), errno, strerror(errno));
    }

    else{
        printf("\nERROR, can't wait the childs. errno = %d, definded as: %s\n", errno, strerror(errno));
    }

    printf("\nGlobal var = %d\n", var);

    exit(EXIT_SUCCESS);
}