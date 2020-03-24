#include"mysocket.h"

#define BUFF_SIZE 100
void error_handling(char *message);

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char in_message[BUFF_SIZE]={0};
    char out_message[BUFF_SIZE]={0};
    char buffer[BUFF_SIZE] = {0};
    int str_len, msg_len;

    if(argc != 3){
        printf("Usage: %s <ip> <port>\n",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect() error");
    }


    // fputs("Input your file name:",stdout);
    // scanf("%s", buffer);
    int name_len = strlen(buffer);
    strncpy(out_message, (char*)&name_len, 4);
    strncpy(out_message + 4, buffer, strlen(buffer));

    // 测试 close 函数能否响应  EOF 数据
    close(sock);
    return 0;
    
    int cnt = write(sock, out_message , strlen(buffer) + 4);

    int r = read(sock, (char*)&msg_len, 4);
    printf("server send msg len=[%d]\n", msg_len);
    if(r == EOF){
        printf("server has no file");
        error_handling("server closed");
    }

    
    while(str_len < msg_len){
        int fcnt = read(sock, in_message, BUFF_SIZE-1);
        if(fcnt == -1){
            printf("read failed [errno:%d]\n", errno);
            break;
        }
        str_len += fcnt;
        if(str_len % 1024 == 0 ){
            in_message[str_len] = 0;
            printf("%s", in_message);
        }
    }
    // in_message[str_len] = 0;
    // printf("%s", in_message);
    
    close(sock);

    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

