#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void *count_lines(void *argv){
    char *fileName = (char *) argv, line;
    int nLines = 0;

    FILE *file;

    if(fopen(fileName, "r") == NULL){
        perror("Can't open file");
        printf("errno = %d", errno);
        exit(EXIT_FAILURE);
    }

    while(line = fgetc(file) != EOF){
        if(line == '\n'){
            nLines++;
        }
    }


}


int main(int argc, char **argv){
    if(argc < 2){
        perror("Command error");
        printf("errno = %d\n", errno);
        printf("Run example --> ./ej2.exe file1 file2 ...\n");
        exit(EXIT_FAILURE);
    }

    int i, total_lines;
    pthread_t thread;
    printf("I'm the main thread\n");
}