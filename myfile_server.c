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

    do{
        cli_sock = accept(serv_sock, (struct sockaddr*) &cli_addr, &cli_addr_size);
        if(cli_sock == -1){
            error_handling("accept() error");
        }
            int in_len = 0, in_cnt = 0;

            // 测试客户端 close 后是否继续调用 read 函数？有无阻塞？
            // while(1){
            printf("read client msg\n");
            int re = read(cli_sock, (char*)&in_len, 4);
            printf("read result=[%d]\n", re);
            if(re == EOF){
                printf("client close sock\n");
                close(cli_sock);
                continue;
            // }
            }
            while(in_len > in_cnt){
                int cnt = read(cli_sock, buffer+in_cnt, BUFF_SIZE - in_cnt);
                if(cnt == -1){
                    error_handling("read() failed");
                }
                in_cnt += cnt;
            }

            buffer[in_len] = 0;
            printf("client want get file:[%s]\n", buffer);

            int fd = open(buffer,O_RDONLY);
            if(fd == -1 ){
                close(cli_sock);
                printf("open failed[errno:%d]", errno);
                continue;
            }

            int file_len = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, SEEK_SET);
            *(int *)buffer = file_len;
            write(cli_sock, (char*)&file_len, 4);
            int cnt = 0;
            while((cnt = read(fd, buffer, BUFF_SIZE)) != 0){
                write(cli_sock, buffer, cnt);
            }
        
        close(cli_sock);
    }while(1);
    close(serv_sock);
    return 0;
}


void error_handling(char *message){
    fputs(message ,stderr);
    fputc('\n',stderr);
    exit(1);
}