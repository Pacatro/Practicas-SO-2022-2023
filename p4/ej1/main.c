#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc != 2){
        printf("Error, you must write the number of process that you want to create.\nerrno = %d.\n", errno);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]), status;
    pid_t childpid, flag;
    int *memory = NULL, id_memory;

    //-----CREATING A KEY FOR SHARED MEMORY-----//
    key_t key = ftok(".", 33);

    if(key == -1){
        perror("ftok error");
        printf("errno = %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //----------CREATING SHARED MEMORY----------//
    id_memory = shmget(key, sizeof(int)*10, IPC_CREAT | SHM_R | SHM_W);

    if(id_memory == -1){
        printf("Can't get shared memory id\n");
        printf("errno = %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //----------POINTING TO A SHARED MEMORY ZONE----------//
    memory = (int *)shmat(id_memory, NULL, 0);
    if(memory == NULL){
        printf("Can't point to the shared memory\n");
        printf("errno = %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    int count = *memory;
    count = 0;

    for(int i = 0; i<N; i++){
        childpid = fork();

        switch(childpid){
            case -1:
                perror("ERROR, can`t create a child process");
            exit(EXIT_FAILURE);

            case 0:
                printf("I'm the child with ID: %d and my father has ID: %d\n", getpid(), getppid());

                count += 100;
            break; 

            default:
                while((flag == wait(&status)) > 0){
                    if(WIFEXITED(status)){
                        printf("Child ID: %d finished, status = %d\n", flag, WEXITSTATUS(status));
                    } else if(WIFSIGNALED(status)){
                        printf("\nChild ID: %d finished with signal %d\n\n", flag, WTERMSIG(status));
                    }
                }

            exit(EXIT_SUCCESS);
        }
    }

    printf("Count variable = %d\n", count);

    //------------DISASSOCIATE SHARED MEMORY------------//
    if(shmdt((char *)memory) == -1){
        perror("SHMDT ERROR");
        printf("errno = %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}