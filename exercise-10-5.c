#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>


void int_handle(int sig){
    alarm(0);
    char message[10];
    fputs("Do you want quit?(Y to quit):", stdout);
    fgets(message, 10, stdin);
    if(strcmp(message,"Y\n") == 0 || strcmp(message,"y\n") == 0){
        printf("Quit...");
        exit(1);
    }
    alarm(1);
}

void alrm_handle(int sig){
    printf("I am alive\n");
    alarm(1);
}

int main(int argc, char* argv[]){
    struct sigaction act, alrm;
   act.sa_handler = int_handle;
   sigemptyset(&act.sa_mask);
   act.sa_flags = 0;

    alrm.sa_handler = alrm_handle;
    sigemptyset(&alrm.sa_mask);
    alrm.sa_flags = 0;
    sigaction(SIGALRM, &alrm, 0);

    sigaction(SIGINT , &act, 0);

    alarm(1);
    while(1){
        sleep(10);
    }

    return 0;


}