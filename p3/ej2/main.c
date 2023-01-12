#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int par = 0, impar = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void take_index(int array[], int n);
void random_array(int *array, int n);

void *thread(void *arg){
    int index = *(int *)arg, random[5], *total = (int *)malloc(sizeof(int));

    random_array(random, 5);

    if(pthread_mutex_lock(&m) != 0){
        printf("Mutex lock error\n");
        pthread_exit(NULL);
    }

    for(int i = 0; i<5; i++){
        if(index % 2 == 0){
            par += random[i];
            *total += random[i];
        } else{
            impar += random[i];
            *total += random[i];
        }
    }

    if(pthread_mutex_unlock(&m) != 0){
        printf("Mutex unlock error\n");
        pthread_exit(NULL);
    }

    pthread_exit((void *)total);
}

int main(int argc, char **argv){
    srand(time(NULL));

    if(argc != 2){
        printf("You must write the number of threads that you want.\n./ej2.exe N\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), n_order[n], add, impar_sum = 0, par_sum = 0;
    pthread_t threads[n];
    void *sum;

    take_index(n_order, n);

    for(int i = 0; i<n; i++){
        if(pthread_create(&threads[i], NULL, thread, (void *)&n_order[i]) != 0){
            printf("Create error\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<n; i++){
        if(pthread_join(threads[i], &sum) != 0){
            printf("Join error\n");
            exit(EXIT_FAILURE);
        }

        add = *(int *)sum;

        printf("Main --> Thread with index %d return sum value: %d\n", n_order[i], add);

        if(n_order[i] % 2 == 0) par_sum += add;

        else impar_sum += add;
    }

    printf("\nMain --> Impar variable value: %d\n", impar);
    printf("Main --> Sum of return values created by impar thread: %d\n", impar_sum);


    printf("\nMain --> Par variable value: %d\n", par);
    printf("Main --> Sum of return values created by par thread: %d\n", par_sum);

    exit(EXIT_SUCCESS);
}

void take_index(int array[], int n){
    for(int i = 0; i<n; i++){
        array[i] = i+1;
    }
}

void random_array(int *array, int n){    
    for(int i = 0; i<n; i++){
        array[i] = rand() % 11;
    }
}