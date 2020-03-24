#include"./mysocket.h"
void error_handling(char *message);

#define BUFF_SIZE 1024

int main(int argc, char* argv[]){
    int serv_sock;
    int cli_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_size;

    char message[] = "hello world";
    char buffer[BUFF_SIZE] = {0};

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handling("socket error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }

    if(listen(serv_sock, 5) == -1){
        error_handling("listen() error");
    }

    cli_addr_size = sizeof(cli_addr);
    cli_sock = accept(serv_sock, (struct sockaddr*) &cli_addr, &cli_addr_size);
    if(cli_sock == -1){
        error_handling("listen() error");
    }


    // for(int i = 0;i < 3; i++){
    while(1){
        int len = strlen(message);
        int in_len = -1, in_cnt = 0;
        
        strncpy(buffer,(char *) &len, 4);
        strncpy(buffer+4, message, len);
        
        printf("write times: %s\n", buffer);
        write(cli_sock, buffer, len + 4);

        // read(cli_sock, &in_len, 4);
        read(cli_sock, &in_len, 1);
        while(in_len > in_cnt){
            int cnt = read(cli_sock, buffer+in_cnt, BUFF_SIZE - in_cnt);
            if(cnt == -1){
                error_handling("read() failed");
            }
            in_cnt += cnt;
        }
        printf("client sent msg:[%s]\n", buffer);
        sleep(1);
    }
    close(cli_sock);
    close(serv_sock);
    return 0;

}


void error_handling(char *message){
    fputs(message ,stderr);
    fputc('\n',stderr);
    exit(1);
}