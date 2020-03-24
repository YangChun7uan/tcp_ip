#include"mysocket.h"
#include<signal.h>

#define BUF_SIZE 1024

void handling_message(char* msg);
void read_childprocess(int sig){
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("remove pro pid: %d\n", pid);
}

int main(int argc, char* argv[]){
    struct sockaddr_in serv_inaddr, cli_inaddr;
    int serv_sock, cli_sock;
    char message[BUF_SIZE];
    int str_len, i;
    socklen_t cli_adr_sz;

    struct sigaction act;
    act.sa_handler=read_childprocess;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

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
    while(1){
        cli_sock = accept(serv_sock, (struct sockaddr *)&cli_inaddr, &cli_adr_sz);
        if(cli_sock == -1){
            continue;
        }else{
            puts("new client connect...");
        }
        
        pid_t pid = fork();
        if(pid == -1){
            close(cli_sock);
            continue;
        }
        
        if(pid == 0){
            close(serv_sock);
            while( (str_len = read(cli_sock, message, BUF_SIZE)) != 0){
                write(cli_sock, message, str_len);
            }

            close(cli_sock);
            puts("client disconnect...");
            return 0;
        }
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