#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

void *writeA(){}
void *writeB(){}

int main(){
    pthread_t threads[2];

    for(int i = 0; i<2; i++){
        if(pthread_create(&threads[i], NULL, writeA, NULL)){
            perror("Can't create thread");
            printf("errno = %d --> %s", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<2; i++){
        if(pthread_join(threads[i], NULL)){
            perror("Can't join thread");
            printf("errno = %d --> %s", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}