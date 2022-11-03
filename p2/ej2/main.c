#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

void *count_lines(void *files){
    char *fileName, line[100];
    int lines, *result = malloc(sizeof(int));
    *result = 0;

    fileName = (char *) files;

    printf("\nI'm the thread with PID: %lu\n", pthread_self());

    FILE *file;
    file = fopen(fileName, "r");

    if(file == NULL){
        perror("Can't open file");
        printf("File name -> %s\n", fileName);
        printf("errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(fgets(line, 100, file) != NULL){
        lines++;
    }

    *result += lines;

    printf("Number of lines %s: %d\n", fileName, lines);
    
    fclose(file);

    pthread_exit((void *)result);
}

int main(int argc, char **argv){
    if(argc < 2){
        perror("Command error");
        printf("errno = %d\n", errno);
        printf("Run example --> ./ej2.exe file1 file2 ...\n");
        exit(EXIT_FAILURE);
    }

    int i, j, total_lines = 0, nLines;
    void *line;
    pthread_t thread[argc - 1];
    printf("I'm the main thread\n");
    char *argu;

    for(i = 0; i < (argc - 1); i++){
        argu = argv[i+1];

        if(pthread_create(&(thread[i]), NULL, count_lines, (void *) argu)){
            perror("Thread error.");
            printf("Can't create thread, errno = %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(j = 0; j<(argc -1); j++){
        if(pthread_join(thread[j], &line)){
            perror("Join error.");
            printf("Can't join threads, errno = %d\n", errno);
            exit(EXIT_FAILURE);
        }

        nLines = *(int *) line;

        total_lines += nLines;
    }


    printf("\nTotal lines = %d\n", total_lines);

    exit(EXIT_SUCCESS);
}