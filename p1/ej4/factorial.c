#include <stdio.h>
#include <stdlib.h>

int fact(int n){
    int result = 1;
    for(int i = 1; i <= n; i++){
        result *= i;
    }

    return result;
}

int main(int argc, char **argv){
    if(argc != 2){
        perror("ERROR, YOU MUST WRITE A NUMBER IN THE COMMAND LINE (./a.out x)\n");
        exit(EXIT_FAILURE);
    }

    int result, n = atoi(argv[1]);

    result = fact(n);

    printf("%d! = %d\n", n, result);

    exit(EXIT_SUCCESS);
}