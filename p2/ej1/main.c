/*no se como hacer que una hebra cree 
distintos numeros aleatorios.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 
#include <errno.h>

void *randomAdd(void *result){
    float random1, random2, *randAdd;
    randAdd = (float *) result;

    printf("\nI'm a thread, PID: %u\n", (unsigned int) pthread_self());

    srand(time(NULL));

    random1 = rand() % 11;
    random2 = rand() % 11;

    printf("Random1 = %f\n", random1);
    printf("Random2 = %f\n", random2);

    *randAdd = random1 + random2;

    printf("Random1 + Random2 = %f\n", *randAdd);

    printf("Thread finished!\n");

    pthread_exit(NULL);
}

int main(){
    int nThread, i;
    float result, main_result = 0;
    
    printf("I'm the main thread!\n");
    printf("Number of threads you want to create: ");
    scanf("%d", &nThread);

    pthread_t threads[nThread];

    for(i = 0; i<nThread; i++){
        if(pthread_create(&(threads[i]), NULL, (void *) randomAdd, (void *) &result)){
            perror("Error creating thread \n");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }

        main_result += result;

        for(int j = 0; j<nThread; j++){
            if(pthread_join(threads[i], NULL)){
                perror("Error joining thread \n");
                printf("errno = %d", errno);
                exit(EXIT_FAILURE);
            }
        }


    }

    printf("\nGolbal result = %f\n", main_result);
    printf("Main thread finished!\n");

    exit(EXIT_SUCCESS);
}