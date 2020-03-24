#include"mysocket.h"

#define TTL_ 50

int main(int argc, char* argv[]){
    struct sockaddr_in multi_adr;
    int send_sock;
    FILE* fp;
    int time_alive = TTL_;
    char buffer[BUF_SIZE];

    if(argc != 3){
        printf("Usage:%s <multip> <port>\n", argv[0]);
        exit(1);
    }

    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(send_sock == -1){
        printf("socket() error\n");
        exit(1);
    }

    memset(&multi_adr, 0, sizeof(multi_adr));
    multi_adr.sin_family = AF_INET;
    multi_adr.sin_addr.s_addr = inet_addr(argv[1]);
    multi_adr.sin_port = htons(atoi(argv[2]));

    setsockopt(send_sock, IPPROTO_IP,
    IP_MULTICAST_TTL, (void*)&time_alive, sizeof(time_alive));

    if((fp = fopen("news.txt", "r")) == NULL){
        printf("open file error\n");
        exit(1);
    }

    while(!feof(fp)){
        fgets(buffer, BUF_SIZE, fp);
        sendto(send_sock, buffer, strlen(buffer),
        0, (struct sockaddr*)&multi_adr, sizeof(multi_adr));
        sleep(2);
    }

    fclose(fp);
    close(send_sock);
    return 0;
}