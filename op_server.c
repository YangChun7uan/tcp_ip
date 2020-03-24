#include"mysocket.h"

#define BUF_SIZE 1024
#define OPSZ 4

void handling_message(char* msg);
unsigned int calculate(int op_cnt, const int* op_expre, char op);


int main(int argc, char* argv[]){
    struct sockaddr_in serv_inaddr, cli_inaddr;
    int serv_sock, cli_sock;
    char message[BUF_SIZE];
    int str_len, op_cnt, i;
    socklen_t cli_adr_sz;

    if(argc != 2){
        printf("Usage:%s port\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        handling_message("Socket() Failed");
    }

    memset(&serv_inaddr, 0, sizeof(serv_inaddr));
    serv_inaddr.sin_family = AF_INET;
    serv_inaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_inaddr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr *) &serv_inaddr, sizeof(serv_inaddr)) == -1){
        handling_message("bind() failed");
    }

    if(listen(serv_sock,5) == -1){
        handling_message("listen() failed");
    }

    cli_adr_sz = sizeof(cli_inaddr);
    int count;
    for(i=0; i<5; i++){
        cli_sock = accept(serv_sock, (struct sockaddr *)&cli_inaddr, &cli_adr_sz);
        if(cli_sock == -1){
            handling_message("accept() failed");
        }

        do{
        read(cli_sock, &op_cnt, 1);
        if(op_cnt == 'Q' || op_cnt == 'q'){
            break;
        }

        memset(message,0,BUF_SIZE);
        while((op_cnt * OPSZ + 1) > str_len){
            int rev_cont = read(cli_sock, &message[str_len], BUF_SIZE - str_len);
            str_len += rev_cont;
        } 
        // char op = message[op_cnt * OPSZ + 1];
        char op = message[str_len - 1];
        int result = calculate(op_cnt, (int *)message, op);
        write(cli_sock, (char*)&result,4);
        }while(1);

        close(cli_sock);
    }

    close(serv_sock);
    return 0;

}

void handling_message(char* msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

unsigned int calculate(int op_cnt, const int* op_expre, char op){
    unsigned int result = op_expre[0];

    switch(op){
        case '+':
            for (int i = 1; i < op_cnt; i++) result +=  op_expre[i];
            break;
        case '-':
            for (int i = 1; i < op_cnt; i++) result -=  op_expre[i];
            break;
        case '*':
            for (int i = 1; i < op_cnt; i++) result *=  op_expre[i];
            break;
        default:
            handling_message("calculate() failed");
    }

    return result;
}