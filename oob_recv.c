#include"mysocket.h"

void urg_handle(int sg);

int srv_sock;
int cln_sock;

int main(int argc, char* argv[]){
    struct sockaddr_in srv_adr, cln_adr;
    struct sigaction act;
    // int srv_sock, cln_sock
    char buffer[BUF_SIZE] = {0};
    int str_len;

    srv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(srv_sock == -1){
        printf("socket() error\n");
        exit(1);
    }

    memset(&srv_adr, 0, sizeof(srv_adr));
    srv_adr.sin_family = AF_INET;
    srv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_adr.sin_port = htons(atoi(argv[1]));

    bind(srv_sock, (struct sockaddr*)&srv_adr, sizeof(srv_adr));

    listen(srv_sock, 5);

    socklen_t cln_adr_sz = sizeof(cln_adr);
    cln_sock = accept(srv_sock, (struct sockaddr*)&cln_adr, &cln_adr_sz);

    fcntl(cln_sock, F_SETOWN, getpid());
    act.sa_handler = urg_handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGURG, &act, 0);

    while( (str_len = recv(cln_sock, buffer, BUF_SIZE, 0)) != 0){
        if(str_len == -1){
            continue;
        }
        buffer[str_len] = 0;
        puts(buffer);
    }

    close(srv_sock);
    close(cln_sock);

    return 0;
}

void urg_handle(int sg){
    int str_len;
    char buffer[BUF_SIZE] = {0};
    str_len = recv(cln_sock, buffer, BUF_SIZE, MSG_OOB);
    buffer[str_len] = 0;
    printf("OOB message[%s]\n", buffer);
}