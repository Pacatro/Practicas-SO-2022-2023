#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <errno.h>
#include <time.h>

int par = 0, impar = 0; //Global

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

//------------ADITIONAL------------
void nArray(int n, int *array);
void nRandomArray(int n, int *array);
//-----------------------------------

void *add(void *value){
    int index = *(int*) value, randoms[5], *total = (int *)malloc(sizeof(int)), i, j;
    *total = 0;

    printf("Thread %lu, with index %d\n", pthread_self(), index);

    if(pthread_mutex_lock(&mtx) != 0){
        printf("Mutex_lock error...\n");
        pthread_exit(NULL);
    }

    nRandomArray(5, randoms);

    if(index % 2 == 0){
        printf("Adding pares....\n");        
        for(i = 0; i < 5; i++){
            par += randoms[i];
        }

    } else{
        printf("Adding impares....\n");
        for(j = 0; j < 5; j++){
            impar += randoms[j];
        }
    }

    *total += par + impar;

    if(pthread_mutex_unlock(&mtx) != 0){
        printf("Mutex_unlock error...\n");
        pthread_exit(NULL);
    }

    pthread_exit((void*) total);
}

int main(int argc, char **argv){
    if(argc != 2){
        perror("You need to write the number of threads (n)");
        printf("./ej2.exe N\nerrno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), values[n], total_int = 0;
    void *total;
    pthread_t threads[n];

    nArray(n, values);

    for(int i = 0; i<n; i++){
        if(pthread_create(&threads[i], NULL, add, (void *)&values[i])){
            perror("Can't create clients threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<n; i++){
        if(pthread_join(threads[i], &total)){
            perror("Can't create clients threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }

        total_int += *(int*)total;
    }

    printf("\nPar = %d\nImpar = %d\nTotal = %d\n", par, impar, *(int*)total);

    printf("\nGlobal total = %d\n", total_int);

    exit(EXIT_SUCCESS);
}

void nArray(int n, int *array){
    for(int i = 0; i < n; i++){
        array[i] = i+1;
    }
}

void nRandomArray(int n, int *array){
    srand(time(NULL));
    
    for(int i = 0; i < n; i++){
        array[i] = rand() % 11;
    }
}