#include"mysocket.h"

int main(int argc, char* argv[]){
    char buffer[BUF_SIZE] = {0};
    struct sockaddr_in srv_adr;
    int cln_sock;

    cln_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(cln_sock == -1){
        printf("socket() error\n");
        exit(12);
    }

    memset(&srv_adr, 0, sizeof(srv_adr));
    srv_adr.sin_family = AF_INET;
    srv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    srv_adr.sin_port = htons(atoi(argv[2]));

    connect(cln_sock, (struct sockaddr*)&srv_adr,sizeof(srv_adr));

    write(cln_sock, "123", 3);
    sleep(3);
    send(cln_sock, "4", 1, MSG_OOB);
    write(cln_sock, "567", 3);
    // send(cln_sock, "890", 3, MSG_OOB);

    close(cln_sock);
    return 0;

}