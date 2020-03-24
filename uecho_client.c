#include"mysocket.h"

#define BUF_SIZE 30

void error_handling(char *msg);

int main(int argc, char* argv[]){
    int cln_sock;
    struct sockaddr_in from_adr, serv_adr;
    int str_len;
    socklen_t cln_adr_sz;
    char in_buffer[BUF_SIZE];
    char out_buffer[BUF_SIZE];

    if(argc != 3){
        printf("Usge %s ip port\n", argv[0]);
        exit(1);
    }

    cln_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(cln_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    socklen_t srv_adr_sz = sizeof(serv_adr);

    while(1){
        fputs("what you want echo(Q/q to quit):", stdout);
        // scanf("%s", out_buffer);
        fgets(out_buffer, BUF_SIZE, stdin);
        if(strcmp(out_buffer, "Q\n") == 0 || strcmp(out_buffer, "q\n") == 0){
            break;
        }
        str_len = strlen(out_buffer);

        sendto(cln_sock, out_buffer, str_len, 0,
        (struct sockaddr*)&serv_adr, srv_adr_sz);

        str_len = recvfrom(cln_sock, in_buffer, BUF_SIZE, 0,
        (struct sockaddr*)&from_adr, &srv_adr_sz);

        in_buffer[str_len] = 0;

        printf("recv from server:--%s", in_buffer);

    }
    close(cln_sock);
    return 0;
}

void error_handling(char *msg){
    printf("%s\n", msg);
    exit(1);
}