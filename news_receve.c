#include"mysocket.h"

int main(int argc, char* argv[]){
    int recv_sock;
    char str_len;
    char buffer[BUF_SIZE];
    struct sockaddr_in adr;
    struct ip_mreq join_adr;
    if(argc != 3){
        printf("Usage:%s <groupip> <port>\n", argv[0]);
        exit(1);
    }

    recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[2]));

    if(bind(recv_sock, (struct sockaddr*)&adr, sizeof(adr)) == -1){
        printf("bind() error\n");
        exit(1);
    }

    join_adr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    join_adr.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(recv_sock, IPPROTO_IP,
    IP_ADD_MEMBERSHIP, (void*)&join_adr, sizeof(join_adr));

    while(1){
        str_len = recvfrom(recv_sock, buffer, BUF_SIZE - 1, 0, NULL, 0);
        if(str_len < 0){
            break;
        }
        buffer[str_len] = 0;
        fputs(buffer, stdout);
    }

    close(recv_sock);
    return 0;



    return 0;
}