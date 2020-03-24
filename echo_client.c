#include"mysocket.h"

//#define BUF_SIZE 10
void handling_message(char* msg);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in cli_inaddr;
    socklen_t str_len;
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

    while(1){
        fputs("Input message(Q for quit):", stdout);
        fgets(message, BUF_SIZE, stdin);

        if(strcmp(message,"q\n") ==0 || strcmp(message,"Q\n")==0){
            break;
        }

        str_len = write(sock, message, strlen(message));
        int rev_len = 0;

        while(rev_len < str_len){
            int rev_cnt = read(sock, &message[str_len], BUF_SIZE-1);
            if(rev_cnt == -1){
                handling_message("read() failed");
            }

            rev_len += rev_cnt;
        }
        message[rev_len] = 0;
        printf("Message from server: %s", message);
    }

    close(sock);
    return 0;



}

void handling_message(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
