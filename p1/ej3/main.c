#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void child1(pid_t childpid, pid_t flag, int status, char **argv){
    childpid = fork();

    switch(childpid){
        case -1:
            perror("ERROR, CAN'T CREATE CHILD PROCESS\n");
            printf("errno value = %d\n", errno);
        exit(EXIT_FAILURE);

        case 0:
            printf("I'm the child number 1, PID: %d, PPID: %d. Running calculator...\n", getpid(), getppid());

            if(system(argv[1]) == -1){
                perror("Can't excute calculator");
                printf("errno value = %d\n", errno);
                exit(EXIT_FAILURE);
            }

        default:
            printf("I'm the father with PID: %d\n", getpid());

            while((flag = wait(&status)) > 0){
                if(WIFEXITED(status)){
                    printf("Father PID: %d, child with PID %d finished, status = %d\n", getpid(), childpid, WEXITSTATUS(status));
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
    }
}

void child2(pid_t childpid, pid_t flag, int status, char **argv){
    childpid = fork();
    switch(childpid){
        case -1:
            perror("ERROR, CAN'T CREATE CHILD PROCESS\n");
            printf("errno value = %d\n", errno);
        exit(EXIT_FAILURE);

        case 0:
            printf("I'm the child number 1, PID: %d, PPID: %d. Running calculator...\n", getpid(), getppid());

            if(execlp(argv[2], argv[3], argv[4]) == -1){
                perror("Can't excute the second order");
                printf("errno value = %d\n", errno);
                exit(EXIT_FAILURE);
            }

        default:
            printf("I'm the father with PID: %d\n", getpid());

            while((flag = wait(&status)) > 0){
                if(WIFEXITED(status)){
                    printf("Father PID: %d, child with PID %d finished, status = %d\n", getpid(), childpid, WEXITSTATUS(status));
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
    }
}

int main(int argc, char **argv){
    /*
    if(argc != 1){
        printf("You must write the name of the executables and the files name: (./program.out 'executable1' 'executable2' 'file1.txt', 'file2.txt'...)\n");
        exit(EXIT_FAILURE);
    }
    */

    pid_t childpid, flag;
    int status;

    printf("Running child 1\n");
    child1(childpid, flag, status, argv);
    
    sleep(10);

    printf("\nRunning child 2\n");
    child2(childpid, flag, status, argv);
    
    exit(EXIT_SUCCESS);
}