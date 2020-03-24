#include"mysocket.h"


int main(int argc, char* argv[]){
    int srv_sock, cln_sock;
    struct sockaddr_in srv_adr, cln_adr;
    fd_set reads,cpy_reads;
    struct timeval timeout;
    int str_len, fd_max, fd_nums;
    socklen_t cln_adr_sz;
    char buffer[BUF_SIZE] = {0};

    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    srv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(srv_sock == -1){
        printf("socket() error\n");
        exit(1);
    }

    memset(&srv_adr, 0, sizeof(srv_adr));
    srv_adr.sin_family = AF_INET;
    srv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(srv_sock, (struct sockaddr*)&srv_adr, sizeof(srv_adr)) == -1){
        printf("bind() error\n");
        exit(1);
    }

    listen(srv_sock, 5);

    FD_ZERO(&reads);  
    FD_SET(srv_sock, &reads);
    fd_max = srv_sock + 1;

    while(1){
        cpy_reads = reads;
        timeout.tv_sec = 3;
        fd_nums =  select(fd_max, &cpy_reads, 0, 0, &timeout);
        if(fd_nums == -1){
            printf("select error: %d\n", errno);
            break;
        }else if(fd_nums == 0){
            continue;
        }

        for(int i = 0; i < fd_max; i++){
            if(FD_ISSET(i, &cpy_reads)){
                if(i == srv_sock){
                    cln_adr_sz = sizeof(cln_adr);
                    cln_sock = accept(srv_sock, (struct sockaddr*)&cln_adr, &cln_adr_sz);
                    FD_SET(cln_sock, &reads);
                    if(cln_sock >= fd_max){
                        fd_max = cln_sock + 1;
                    }
                    printf("Client connect...\n");
                }else{
                    str_len = read(cln_sock, buffer, BUF_SIZE);
                    if(str_len == 0){
                        FD_CLR(i, &reads);
                        close(i);
                        printf("Clinet disconnect...[%d]\n", i);
                    }else{
                        buffer[str_len] = 0;
                        printf("Message from client:%s\n", buffer);
                        write(i, buffer, str_len);
                    }
                }
            }
        }
    }

    close(srv_sock);
    return 0;

}

