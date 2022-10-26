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

/****************************
 NO SE COMO DIVIDIR EL VECTOR
 
int sum_elements(void *num){
    int num = (int ) num;
    int result, i;

    for(i = 0; i<num; i++){
        randomArray[i]
    }
}
*****************************/

int main(int argc, char **argv){
    if(argc != 2){
        perror("Command error");
        printf("errno = %d\n", errno);
        printf("Run example --> ./ej3.exe num\n");
        exit(EXIT_FAILURE);
    }

    printf("Main thread!\n");

    int num = atoi(argv[1]), i, randArray[N];
    pthread_t threads[num];

    write_in_array(randArray);

    for(i = 0; i<num; i++){
        if(pthread_create(&(threads[i]), NULL, (void *) sum_elements, (void *) num)){
            perror("Thread error.");
            printf("Can't create thread, errno = %d\n", errno);
            exit(EXIT_FAILURE);
        }

        if(pthread_join(threads[i], NULL)){
            perror("Join error.");
            printf("Can't join threads, errno = %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
}