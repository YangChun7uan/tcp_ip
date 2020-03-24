#include"mysocket.h"


int main(int argc, char* argv[]){
    struct sockaddr_in in_adr;
    struct hostent *host;

    memset(&in_adr, 0, sizeof(in_adr));
    in_adr.sin_addr.s_addr = inet_addr(argv[1]);
    host = gethostbyaddr((char*) &in_adr.sin_addr, 4, AF_INET);
    if(!host){
        printf("gethost error\n");
        return 0;
        
    }

    printf("Office name : %s\n", host->h_name);
    for(int i = 0; host->h_aliases[i]; i++){
        printf("Alias %d: %s\n", i+1, host->h_aliases[i]);
    }

    return 0;


}