#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

sem_t a, b;

void *escribirA(){
    int i;
    for (i= 0; i<5; i++){

        if(sem_wait(&a) != 0){
            perror("Sem wait error");
            printf("errno = %d, %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        printf ("A");
        fflush(NULL);

        if(sem_post(&b) != 0){
            perror("Sem post error");
            printf("errno = %d, %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

    }
    
    pthread_exit(NULL);
}

void *escribirB(){
    int i;

    for (i= 0; i<5; i++){

        if(sem_wait(&b) != 0){
            perror("Sem wait error");
            printf("errno = %d, %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        printf ("B");
        fflush(NULL);

        if(sem_post(&a) != 0){
            perror("Sem post error");
            printf("errno = %d, %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }
    }
    
    pthread_exit(NULL);
}

int main(){
    pthread_t A, B;
    
    if(sem_init(&a, 0, 0) != 0){
        perror("Sem init error");
        printf("errno = %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(sem_init(&b, 0, 1) != 0){
        perror("Sem init error");
        printf("errno = %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&A, NULL, escribirA, NULL) != 0){
        printf("Create A error\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&B, NULL, escribirB, NULL) != 0){
        printf("Create B error\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_join(A, NULL) != 0){
        printf("Join A error\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_join(B, NULL) != 0){
        printf("Join B error\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");

    exit(EXIT_SUCCESS);
}