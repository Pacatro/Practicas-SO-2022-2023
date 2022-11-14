#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define N 10

void write_in_array(int *randArray);

void show_array(int *array, int n);

struct divided_array{
    int *v;
    int init;
    int end;
};

void *sum_elements_array(void *array){
    struct divided_array *mid_array = (struct divided_array *) array;
    int *result = malloc(sizeof(int));
    *result = 0;

    printf("\nThread with TID: %lu\n", pthread_self());
    printf("Vector: ");
    for(int i = mid_array->init; i<mid_array->end; i++){
        printf("%d ", (mid_array->v)[i]);
        *result += (mid_array->v)[i];
    }
    
    printf("\nResult = %d\n", *result);

    pthread_exit((void *) result);
}

int main(int argc, char **argv){
    if(argc != 2){
        perror("Command error");
        printf("errno = %d\n", errno);
        printf("Run example --> ./ej3.exe num\n");
        exit(EXIT_FAILURE);
    }

    int num = atoi(argv[1]);

    if(num != 2 && num != 5){
        printf("ERROR, INCORRECT VALUE (2 OR 5)\n");
        exit(EXIT_FAILURE);
    }

    printf("Main thread!\n");

    int i, j ,randArray[N], total_result = 0, result;
    pthread_t threads[num];
    void *result_return;

    write_in_array(randArray);

    printf("Main array: ");
    show_array(randArray, N);
    printf("\n");

    struct divided_array struct_array[num];

    int init = 0;
    int end = (N/num)-1;

    for(i = 0; i<num; i++){
        struct_array[i].v = randArray;

        struct_array[i].init = init;
        init += (N/num);

        struct_array[i].end = end;
        end += (N/num);
    }

    for(i = 0; i<num; i++){
        if(pthread_create(&threads[i], NULL, sum_elements_array, (void *) &struct_array[i])){
            perror("Thread error");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(j = 0; j<num; j++){
        if(pthread_join(threads[j], &result_return)){
            perror("Join error");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }

        result = *(int *)result_return;

        total_result += result;  

    }

    printf("\nTotal result = %d\n", total_result);

    exit(EXIT_SUCCESS);

}

void write_in_array(int *randArray){
    int i;

    srand(time(NULL));

    for(i = 0; i<N; i++){
        randArray[i] = rand() % 10;
    }
}

void show_array(int *array, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
}
