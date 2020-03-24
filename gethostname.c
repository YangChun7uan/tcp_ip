#include"mysocket.h"


int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <hostname>\n", argv[0]);
        exit(1);
    }

    struct hostent *host;

    host = gethostbyname(argv[1]);
    if(!host){
        printf("gethostbyname() error\n");
        exit(1);
    }

    printf("Offical Name: %s\n", host->h_name);
    for(int i=0; host->h_aliases[i]; i++){
        printf("Aliases %d: %s \n",i+1, host->h_aliases[i]);
   
}

    for(int i=0; host->h_addr_list[i]; i++){
        printf("IP Addr %d: %s\n", i+1,
        inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
    }
    return 0;
}