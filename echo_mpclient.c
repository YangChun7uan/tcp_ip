#include"mysocket.h"
#include<signal.h>

#define BUF_SIZE 10
void handling_message(char* msg);

void read_childprocess(int sig){
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("remove pro pid: %d\n", pid);
}

void read_route(int sock, char *buffer);
void write_route(int sock, char *buffer);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in cli_inaddr;
    socklen_t str_len;
    char message[BUF_SIZE];
    struct sigaction act;

    if(argc != 3){
        printf("Usage: %s ip port\n",argv[0]);
        exit(1);
    }

    act.sa_handler = read_childprocess;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

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

    pid_t pid = fork();

    if(pid == 0){
        read_route(sock, message);
    }else{
        write_route(sock, message);
    }

    close(sock);

    return 0;



}

void handling_message(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_route(int sock, char *buffer){
    while(1){
        int str_len = read(sock, buffer, BUF_SIZE);
        if(str_len == 0){
            printf("client read end\n");
            break;
        }
        buffer[str_len] = 0;
        printf("Message from server:%s\n", buffer);
    }

    return ;

}
void write_route(int sock, char *buffer){
    while(1){
        fputs("Input your message:", stdout);
        fgets(buffer,BUF_SIZE, stdin);
        if(!strcmp(buffer,"q\n")||!strcmp(buffer, "Q\n")){
            shutdown(sock, SHUT_WR);
            break;
        }
        write(sock, buffer, strlen(buffer));
    }

    return ;

}