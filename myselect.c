#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>

#define BUF_SIZE 30

int main(int argc, char* argv[]){
    fd_set reads, temps;
    int result, str_len;
    char buffer[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads);

    timeout.tv_sec = 3;
    // timeout.tv_usec = 500;

    while(1){
        temps = reads;
    // timeout.tv_sec = 4;
    // timeout.tv_usec = 500;
        result = select(1, &temps,0, 0, &timeout);
        if(result == -1){
            puts("select error");
            break;
        }else if(result == 0){
            puts("timesout");
        }else{
            if(FD_ISSET(0, &temps)){
                str_len = read(0, buffer, BUF_SIZE);
                buffer[str_len] = 0;
                printf("message from stdin:%s\n", buffer);
            }
        }
    }
    return 0;
}