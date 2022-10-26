#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int global = 0; //Global variable

void *loop(){
    printf("\nThread with TID: %lu\n", pthread_self());
    int i = 0;

    while(i != 1000){
        global++;
        i++;
    }
}

int main(){
    pthread_t thread1, thread2;

    if(pthread_create(&thread1, NULL, (void *) loop, NULL)){
        perror("Thread error.");
        printf("Can't create thread, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&thread2, NULL, (void *) loop, NULL)){
        perror("Thread error.");
        printf("Can't create thread, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    if(pthread_join(thread1, NULL)){
        perror("Join error.");
        printf("Can't join threads, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    if(pthread_join(thread2, NULL)){
        perror("Join error.");
        printf("Can't join threads, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("\nGlobal = %d\n", global);
}