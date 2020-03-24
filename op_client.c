#include"mysocket.h"

#define BUF_SIZE 1024
#define OPSZ 4
void handling_message(char* msg);

int main(int argc, char *argv[])
{

    int sock, result;
    struct sockaddr_in cli_inaddr;
    socklen_t str_len = 0;
    char message[BUF_SIZE];

    if(argc != 3){
        printf("Usage: %s ip port\n",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        handling_message("socket() failed");
    }

    memset(&cli_inaddr, 0, sizeof(cli_inaddr));
    cli_inaddr.sin_family = AF_INET;
    cli_inaddr.sin_addr.s_addr = inet_addr(argv[1]);
    cli_inaddr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &cli_inaddr, sizeof(cli_inaddr)) == -1){
        handling_message("connect() failed");
    }else{
        puts("connect ...");
    }

    int count, op_num, operation; 
    while(1){
        memset(message,0, BUF_SIZE);
        fputs("Input Ope Count(Q for quit):", stdout);
        scanf("%d",&count);
        printf("count: %d\n", count);

        message[0]=(char)count;

        int i = 0;
        for(i = 0; i < count; i++){
            fputs("Operant:", stdout);
            scanf("%d", (int *)&message[i*OPSZ + 1]);
            printf("Input Operant:%d\n", message[i*OPSZ+1]);
        }
        fputs("Operator:", stdout);
        getchar();
        scanf("%c", &message[count * OPSZ + 1]);

        // if(strcmp(message,"q\n") ==0 || strcmp(message,"Q\n")==0){
            // break;
        // }

        str_len = count * OPSZ + 2;
        write(sock, message, str_len);
        int rev_len = 0;

        while(rev_len < OPSZ){
            int rev_cnt = read(sock, &result + rev_len, OPSZ - rev_len);
            if(rev_cnt == -1){
                handling_message("read() failed");
            }
            rev_len += rev_cnt;
        }
        // int * result =(int*) message;
        printf("Result from server: %d\n", result);
        // printf("Result from server: %s\n", *result);
    }

    printf("client exit\n");
    close(sock);

    return 0;



}

void handling_message(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}