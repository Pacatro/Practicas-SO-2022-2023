#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <errno.h>
#include <time.h>

int *tshirts; //global array
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

//-----------------ADITIONAL-----------------//
void nRandomArray(int n, int *array, int max);
void show_tshirts(int n, int *array);
//-------------------------------------------//

void *client_thread(void *arg){
    int model, quantity, m;

    m = *(int*)arg;

    model = rand() % m;
    quantity = rand() % 11;

    if(pthread_mutex_lock(&mtx) != 0){
        printf("Mutex_lock error...\n");
        pthread_exit(NULL);
    }

    tshirts[model] -= quantity;

    if(tshirts[model] < 0){
        tshirts[model] = 0;
    } 

    printf("\n<-- The client %lu bought %d units from the model %d\n", pthread_self(), quantity, model);

    if(pthread_mutex_unlock(&mtx) != 0){
        printf("Mutex_unlock error...\n");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

void *seller_thread(void *arg){
    int model, quantity, m;
    m = *(int*)arg;

    model = rand() % m;
    quantity = rand() % 11;

    if(pthread_mutex_lock(&mtx) != 0){
        printf("Mutex_lock error...\n");
        pthread_exit(NULL);
    }

    tshirts[model] += quantity;

    printf("\n--> The seller %lu add %d units to the model %d\n", pthread_self(), quantity, model);

    if(pthread_mutex_unlock(&mtx) != 0){
        printf("Mutex_unlock error...\n");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv){
    if(argc != 3){
        perror("You need to write the number of clients (n) and sellers (m)");
        printf("./ej1.exe N M\nerrno = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), m = atoi(argv[2]);
    pthread_t clients[n], sellers[m];
    void *arg = &m;

    tshirts = (int*)malloc(m*sizeof(int));

    nRandomArray(m, tshirts, 100);
    
    printf("Tshirts on sale: ");
    show_tshirts(m, tshirts);
    printf("\n");

//-----------Creating threads-----------
    for(int i = 0; i<n; i++){
        if(pthread_create(&clients[i], NULL, client_thread, arg)){
            perror("Can't create clients threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<m; i++){
        if(pthread_create(&sellers[i], NULL, seller_thread, arg)){
            perror("Can't create sellers threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

//-----------Joining threads-----------
    for(int i = 0; i<n; i++){
        if(pthread_join(clients[i], NULL)){
            perror("Can't create clients threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<m; i++){
        if(pthread_join(sellers[i], NULL)){
            perror("Can't create sellers threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    printf("\nTshirts on sale: ");
    show_tshirts(m, tshirts);
    printf("\n");

    free(tshirts);

    exit(EXIT_SUCCESS);
}

void nRandomArray(int n, int *array, int max){
    srand(time(NULL));
    
    for(int i = 0; i<n; i++){
        array[i] = rand() % max+1;
    }
}

void show_tshirts(int n, int *array){
    for(int i = 0; i<n; i++){
        printf("%d ", array[i]);
    }
}