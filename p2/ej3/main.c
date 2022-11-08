#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define N 10

void write_in_array(int randArray[]){
    int i;

    srand(time(NULL));

    for(i = 0; i<N; i++){
        randArray[i] = rand() % 10;
    }
}

void show_array(int array[], int n){
    for(int i = 0; i<n; i++){
        printf("%d ", array[i]);
    }
}

void divided_array(int randArray[], int array[], int num){
    for(int i = 0; i<(N/num); i++){
        array[i] = randArray[i];
    }
}

void *sum_elements_array(void *array){

}

int main(int argc, char **argv){
    if(argc != 2){
        perror("Command error");
        printf("errno = %d\n", errno);
        printf("Run example --> ./ej3.exe num\n");
        exit(EXIT_FAILURE);
    }

    printf("Main thread!\n");

    int num = atoi(argv[1]), i, j ,randArray[N];
    pthread_t threads[num];

    write_in_array(randArray);

    printf("Vector 1: ");
    show_array(randArray, N);

    int array[N/num];

    divided_array(randArray, array, num);

    printf("\nVector 2: ");
    show_array(array, N/num);

/*
    for(i = 0; i<num; i++){
        if(pthread_create(&threads[i], NULL, sum_elements_array, randArray)){
            perror("Thread error");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(j = 0; j<num; j++){
        if(pthread_join(threads[j], NULL)){
            perror("Join error");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

*/

    exit(EXIT_SUCCESS);

}