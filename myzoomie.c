#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void read_childproc(int sig){
    int status;
    printf("before waitpid\n");
    sleep(10);
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("after waitpid\n");
    sleep(10);
    if(WIFEXITED(status)){
        printf("Child process end[%d]\n", pid);
        printf("Child process send msg:%d\n", WEXITSTATUS(status));
    }
}

int gval = 10;

int main(int argc ,char* argv[]){
    pid_t pid;
    int lval = 20;
    gval ++ ,lval+= 5;

        struct sigaction act;
        act.sa_handler=read_childproc;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGCHLD, &act, 0);

    pid = fork();
    if(pid == 0){
        gval++, lval+=2;
    }
    else{
        gval -= 2;
        lval -= 2;
    }

    if(pid == 0){
        printf("I am child process\n");
        // printf("Child process gval=%d lval=%d\n", gval, lval);
    }else{
        printf("Child process pid = %d\n", pid);
    }

    if(pid == 0){
        printf("Child process end\n");
        exit(9);
    }else{
        // int status = 0;
        // int result = wait(&status);

        for(int i = 0; i<3; i++){
            sleep(3);
        }
        // if(result == -1){
            // printf("Child process return failed\n");
        // }
        // if(WIFEXITED(status)){
            // printf("Child return value = %d\n", WEXITSTATUS(status));
        // }
        printf("Parent process end\n");
    }

    return 0;
}