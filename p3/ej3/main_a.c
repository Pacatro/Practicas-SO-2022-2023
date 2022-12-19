#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <time.h>

sem_t s;
sem_t n;
sem_t e;

int array[5];

//-----------------ADITIONAL-----------------//
void show_array(int n, int *array);
void nRandomArray(int n, int *array, int max);
int nrandom();
//-------------------------------------------//

void *producer(){
    for(int i = 0; i<5; i++){
        if(sem_wait(&e) != 0){
            printf("sem_wait error...\n");
            printf("errno value= %d --> %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        if(sem_wait(&s) != 0){
            printf("sem_wait error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        nRandomArray(5, array, 10);

        if(sem_post(&s) != 0){
            printf("sem_post error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        if(sem_post(&n) != 0){
            printf("sem_post error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}
void *consumer(){
    for(int i = 0; i<5; i++){
        if(sem_wait(&n) != 0){
            printf("sem_wait error...\n");
            printf("errno value= %d --> %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        if(sem_wait(&s) != 0){
            printf("sem_wait error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        array[nrandom()] = 0;

        if(sem_post(&s) != 0){
            printf("sem_post error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }

        if(sem_post(&e) != 0){
            printf("sem_post error...\n");
            printf("errno value= %d definido como %s\n", errno, strerror(errno));
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t p, c;

    if(sem_init(&s, 0, 1) != 0){
        printf("sem_init error\n");
        printf("errno value = %d, %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(sem_init(&n, 0, 0) != 0){
        printf("sem_init error\n");
        printf("errno value = %d, %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(sem_init(&e, 0, 5) != 0){
        printf("sem_init error\n");
        printf("errno value = %d, %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("Array: ");
    show_array(5, array);

    if(pthread_create(&p, NULL, producer, NULL)){
        perror("Can't create thread");
        printf("errno = %d --> %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_join(p, NULL)){
        perror("Can't create thread");
        printf("errno = %d --> %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("\nArray producer: ");
    show_array(5, array);

    if(pthread_create(&c, NULL, consumer, NULL)){
        perror("Can't create thread");
        printf("errno = %d --> %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_join(c, NULL)){
        perror("Can't create thread");
        printf("errno = %d --> %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("\nArray: ");
    show_array(5, array);
    printf("\n");

    exit(EXIT_SUCCESS);
}

void show_array(int n, int *array){
    for(int i = 0; i<n; i++){
        printf("%d ", array[i]);
    }
}

void nRandomArray(int n, int *array, int max){
    srand(time(NULL));
    
    for(int i = 0; i<n; i++){
        array[i] = rand() % max+1;
    }
}

int nrandom(){
    srand(time(NULL));
    return rand() % 5;
}