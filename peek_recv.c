#include"mysocket.h"

int main(int argc, char *argv[]){
    int srv_sock, cln_sock, str_len;
    struct sockaddr_in srv_adr, cln_adr;
    socklen_t cln_adr_sz;
    char buffer[BUF_SIZE];

    srv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&srv_adr, 0, sizeof(srv_adr));
    srv_adr.sin_family = AF_INET;
    srv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_adr.sin_port = htons(atoi(argv[1]));

    bind(srv_sock, (struct sockaddr*)&srv_adr, sizeof(srv_adr));

    listen(srv_sock, 5);

    cln_adr_sz = sizeof(cln_adr);
    cln_sock = accept(srv_sock, (struct sockaddr*)&cln_adr, &cln_adr_sz);

    while(1){
        str_len = recv(cln_sock, buffer, BUF_SIZE, MSG_PEEK|MSG_DONTWAIT);
        if(str_len > 0){
            break;
        }
    }
    buffer[str_len] = 0;
    printf("Receve from client by peek:%s\n", buffer);

    str_len = recv(cln_sock, buffer, BUF_SIZE, 0);
    buffer[str_len] = 0;
    printf("Read again:%s", buffer);
    
    close(cln_sock);
    close(srv_sock);
    return 0;
}