/*no se como hacer que una hebra cree 
distintos numeros aleatorios.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 
#include <errno.h>

void generate_random(float *argu){
    int i;
    srand(time(NULL));

    for(i = 0; i<2; i++){
        argu[i] = rand() % 11;
    }
}

void *randomAdd(void *arg){
    float *argu = (float *)arg;
    float *result = malloc(sizeof(float));
    float rand1, rand2;

    generate_random(argu);

    printf("\nI'm a thread with TID: %lu\n", pthread_self());
    rand1 = argu[0];
    rand2 = argu[1];

    printf("Rand1 = %f\n", rand1);
    printf("Rand2 = %f\n", rand2);

    *result = rand1 + rand2;

    printf("Rand1 + Rand2 = %f\n", *result);

    pthread_exit((void *) result);
}

int main(){
    int nThread, i, j;
    float main_result, arg[2], global_result = 0;
    void *result;
    
    printf("I'm the main thread!\n");
    printf("Number of threads you want to create: ");
    scanf("%d", &nThread);

    pthread_t threads[nThread];

    //Create threads
    for(i = 0; i<nThread; i++){
        if(pthread_create(&(threads[i]), NULL, (void *) randomAdd, (void *) arg)){
            perror("Thread error");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(j = 0; j<nThread; j++){
        if(pthread_join(threads[j], &result)){
            perror("Join error");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }

        main_result = *(float *) result;

        global_result += main_result;

    }

    printf("\nGlobal result = %f\n", global_result);

    exit(EXIT_SUCCESS);
}