#include"mysocket.h"

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in send_adr;
    char buffer[BUF_SIZE] = {0};

    sock = socket(PF_INET,SOCK_STREAM, 0);
    
    memset(&send_adr, 0, sizeof(send_adr));
    send_adr.sin_family = AF_INET;
    send_adr.sin_addr.s_addr = inet_addr(argv[1]);
    send_adr.sin_port = htons(atoi(argv[2]));

    connect(sock, (struct sockaddr*)&send_adr, sizeof(send_adr));

    write(sock, "123", 3 );

    close(sock);
    return 0;
}