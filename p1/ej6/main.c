#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void ring(){
    printf("\n\tRING!!\n");
    return;
}

unsigned int alarm_wait(int seconds){
    alarm(seconds);
    pause();
}

int main(){

    int nRings = 0;

    if(signal(SIGALRM, ring) == SIG_ERR){
        perror("Signal error");
        printf("errno value = %d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("Alarm in 5 seconds...\n");
    alarm_wait(5);

    printf("\nAlarm in 3 seconds...\n");
    alarm_wait(3);

    printf("\nAlarm every second...\n");
    while(nRings != 4){
        alarm_wait(1);
        nRings++;
    }

    if(nRings == 4){
        printf("\nEND OF PROGRAM\n");
        kill(getpid(), SIGKILL);
    }
    
}