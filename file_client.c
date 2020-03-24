#include"mysocket.h"

#define BUF_SZ 1024


int main(int argc, char* argv[]){
    int cln_sock;
    FILE* fd;
    char buffer[BUF_SZ] = {0};
    int str_len, read_cnt;
    struct sockaddr_in srv_adr;

    fd = fopen("./receve.dt", "wb");

    cln_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&srv_adr, 0, sizeof(srv_adr));
    srv_adr.sin_family = AF_INET;
    srv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    srv_adr.sin_port = htons(atoi(argv[2]));

    connect(cln_sock, (struct sockaddr*)&srv_adr, sizeof(srv_adr));

    while((read_cnt = read(cln_sock, buffer, BUF_SZ)) != 0){
        fwrite((void*)buffer, 1, read_cnt, fd);
    }

    fputs("Received file data",stdout);
    write(cln_sock, "thand you", 10);
    fclose(fd);
    close(cln_sock);
    return 0;
}