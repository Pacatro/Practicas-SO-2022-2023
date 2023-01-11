#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

void child1(char **argv){
    if(execlp(argv[1], argv[1], NULL) == -1){
        perror("Can't excute calculator");
        printf("errno value = %d\n", errno);
        exit(EXIT_FAILURE);
    }
}

void child2(char **argv){
    if(execvp(argv[2], &argv[2]) == -1 ){
        perror("Can't excute gedit");
        printf("errno value = %d\n", errno);
        exit(EXIT_FAILURE);
    }
}
