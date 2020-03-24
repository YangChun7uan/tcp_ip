#include"mysocket.h"

#define BUF_SIZE 1024
void handling_message(char* msg);

int main(int argc, char *argv[])
{
    int sock;
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
        fputs("Input Ope Count(Q for quit):", stdout);
        count = getchar() - 48;
        getc(stdin);
        printf("count: %d\n", count);
        int *proty = (int *)malloc(sizeof(int) * (count + 2));
        if(proty == NULL){
            handling_message("malloc failed");
        }

        proty[0]=count;

        for(int i = 0; i < count; i++){
            fputs("Operant:", stdout);
            int operant = getchar();
            fgetc(stdin);
            proty[i+1]=operant - 48;
        }
        fputs("Operator:", stdout);
        int operator = getchar();
        getchar();
        proty[count+1]=operator;

        // if(strcmp(message,"q\n") ==0 || strcmp(message,"Q\n")==0){
            // break;
        // }

        str_len = write(sock, proty, sizeof(int) * (count + 2));
        int rev_len = 0;


        while(rev_len < str_len){
            int rev_cnt = read(sock, &message[rev_len], BUF_SIZE-1);
            if(rev_cnt == -1){
                handling_message("read() failed");
            }

            rev_len += rev_cnt;
        }
        // int * result =(int*) message;
        printf("Result from server: %x\n", message));
        // printf("Result from server: %s\n", *result);
    }

    close(sock);
    return 0;



}

void handling_message(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}