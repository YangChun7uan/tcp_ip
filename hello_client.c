#include"mysocket.h"

#define BUFF_SIZE 100
void error_handling(char *message);

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char in_message[BUFF_SIZE];
    char out_message[BUFF_SIZE];
    // int str_len;

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

    int cnt = read(sock, in_message , BUFSIZ  );
    /*
        close equal send EOF to the server sock
    */


    // do{
    // int cnt = 0, msg_len = 0, str_len = 0;
    // int r = read(sock, (char*)&msg_len , 4);
    // if(r == -1){
    //     error_handling("read() error");
    // }

    // while(str_len < msg_len ){
    //     cnt = read(sock, in_message + str_len , BUFSIZ - str_len);
    //     str_len += cnt;
    // }
    // in_message[str_len]=0;
    // printf("Receive Message:[%s]\n",in_message);

    // strncpy(in_message+str_len, in_message, str_len);
    // str_len += str_len;
    // strncpy(out_message, (char*) &str_len, 4);
    // strncpy(out_message + 4, in_message, str_len); 
    // printf("Send Info[%lu:%s]\n",str_len, out_message+4);
    // int result = write(sock, out_message, str_len + 4);
    // printf("write bytes = %d\n", result);

    // } while(1);

    close(sock);

    return 0;
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

