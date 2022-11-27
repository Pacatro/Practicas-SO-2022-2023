#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include<unistd.h>

#define N 10

int tshirts[N]; //global array
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

//---------------ADITIONAL-----------------
void nRandomArray(int n, int *tshirts, int max);
void show_tshirts(int n, int *tshirts);
int generateNumber();
//-----------------------------------------

void *client_thread(void *arg){
    int model, quantity;

    model = rand() % 11;
    quantity = rand() % 10;

    printf("\nModel: %d\n", model);
    printf("Quantity: %d\n", quantity);

    if(pthread_mutex_lock(&mtx) != 0){
        printf("Mutex_lock error...\n");
        pthread_exit(NULL);
    }

    for(int i = 0; i < N; i++){
        if(i == model){
            tshirts[i] - quantity;
        }
    }    

    printf("The client %lu bought %d units from the model %d\n", pthread_self(), quantity, model);

    if(pthread_mutex_unlock(&mtx) != 0){
        printf("Mutex_unlock error...\n");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

void *seller_thread(void *arg){
    int model, quantity;

    model = rand() % 11;
    quantity = rand() % 10;

    printf("\nModel: %d\n", model);
    printf("Quantity: %d\n", quantity);

    if(pthread_mutex_lock(&mtx) != 0){
        printf("Mutex_lock error...\n");
        pthread_exit(NULL);
    }

    for(int i = 0; i < N; i++){
        if(i == model){
            tshirts[i] + quantity;
        }
    }    

    printf("The seller %lu add %d units to the model %d\n", pthread_self(), quantity, model);

    if(pthread_mutex_unlock(&mtx) != 0){
        printf("Mutex_unlock error...\n");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv){
    if(argc != 3){
        perror("You need to write the number of clients (n) and sellers (m)");
        printf("./ej1.exe N M\nerrno = %d", errno);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), m = atoi(argv[2]), arg[2];
    pthread_t clients[n], sellers[m];

    nRandomArray(N, tshirts, 100);
    
    printf("Tshirts on sale: ");
    show_tshirts(N, tshirts);
    printf("\n");

//-----------Creating threads-----------
    for(int i = 0; i<n; i++){
        if(pthread_create(&clients[i], NULL, client_thread, (void *)arg)){
            perror("Can't create clients threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<n; i++){
        if(pthread_create(&sellers[i], NULL, seller_thread, (void *)arg)){
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

    for(int i = 0; i<n; i++){
        if(pthread_join(sellers[i], NULL)){
            perror("Can't create sellers threads");
            printf("errno = %d", errno);
            exit(EXIT_FAILURE);
        }
    }

    printf("\nTshirts on sale: ");
    show_tshirts(N, tshirts);
    printf("\n");

    exit(EXIT_SUCCESS);
}

void nRandomArray(int n, int *tshirts, int max){
    srand(time(NULL));
    
    for(int i = 0; i<n; i++){
        tshirts[i] = rand() % max+1;
    }
}

void show_tshirts(int n, int *tshirts){
    for(int i = 0; i<n; i++){
        printf("%d ", tshirts[i]);
    }
}