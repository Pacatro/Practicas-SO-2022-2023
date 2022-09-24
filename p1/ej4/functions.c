#include "functions.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void child1(char **argv){
    if(execl("factorial.exe", "./factorial.exe", argv[1], NULL) == -1){
        perror("ERROR, CAN'T EXECUTE ");
        printf("./factorial.exe");
        exit(EXIT_FAILURE);
    }
}

void child2(char **argv){
    if(execl("factorial.exe", "./factorial.exe", argv[2], NULL) == -1){
        perror("ERROR, CAN'T EXECUTE ");
        printf("./factorial.exe");
        exit(EXIT_FAILURE);
    }
}