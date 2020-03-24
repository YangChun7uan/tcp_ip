#include"mysocket.h"

#define BUF_SIZE 30
void error_handling(char* meg);

int main(int argc, char* argv[]){

    int serv_sock;
    char in_buffer[BUF_SIZE];
    char out_buffer[BUF_SIZE];
    int str_len;
    socklen_t cln_adr_sz;

    struct sockaddr_in serv_adr, cln_adr;
    if(argc != 2){
        printf("Usage: %s port\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(serv_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port   = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1 ){
        error_handling("bind() error");
    }

    while(1){
        cln_adr_sz = sizeof(cln_adr);
        str_len = recvfrom (serv_sock, in_buffer, BUF_SIZE,0,
        (struct sockaddr*) &cln_adr, &cln_adr_sz);
        in_buffer[str_len] = {0};
        printf("recvfrom client:%s", in_buffer);

        fputs("send your message for client(q to quit)", stdout);
        fgets(out_buffer, BUF_SIZE, stdin);
        if(!strcmp(out_buffer,"q\n") || !strcmp(out_buffer,"Q\n")){
            break;
        }

        sendto(serv_sock, out_buffer, strlen(out_buffer), 0,
        (struct sockaddr*)&cln_adr, cln_adr_sz);
    }

    close(serv_sock);
    return 0;
}


void error_handling(char *msg){
    fputs(msg, stdout);
    exit(1);
}