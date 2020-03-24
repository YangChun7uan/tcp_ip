#include"mysocket.h"

#define BUF_SZ 1024

void error_handling(char *msg);


int main(int argc, char* argv[]){
    int srv_sock, cln_sock ;
    FILE *fd;
    struct sockaddr_in srv_adr, cln_adr;
    int str_len;
    char buffer[BUF_SZ] = {0};

    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    fd = fopen("./file_server.c", "rb");
    srv_sock = socket(PF_INET, SOCK_STREAM,0);
    if(srv_sock == -1){
        error_handling("socket() error");
    }

    memset(&srv_adr, 0, sizeof(srv_adr));
    srv_adr.sin_family = AF_INET;
    srv_adr.sin_addr.s_addr = INADDR_ANY;
    srv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(srv_sock, (struct sockaddr*)&srv_adr, sizeof(srv_adr)) == -1){
        close(srv_sock);
        error_handling("bind() error");
    }

    listen(srv_sock, 5);

    socklen_t cln_adr_sz = sizeof(cln_adr);
    cln_sock = accept(srv_sock, (struct sockaddr*)&cln_adr, &cln_adr_sz);
    
    while(1){
        int read_cnt = fread((void*)buffer, 1, BUF_SZ, fd);
        if(read_cnt < BUF_SZ){
            write(cln_sock, buffer, read_cnt);
            break;
        }
        write(cln_sock, buffer, BUF_SZ);
    }
    fclose(fd);

    while(1){
        ;
    }

    //shutdown(cln_sock, SHUT_WR);
    //int read_cnt = read(cln_sock, buffer, BUF_SZ);
    //buffer[read_cnt] = 0;

    //printf("Message from client:%s", buffer);
    //fclose(fd);
    //close(srv_sock);
    //close(cln_sock);
    //return 0;

}

void error_handling(char* msg){
    printf("%s", msg);
    exit(1);
}