#include<stdio.h>
#include<unistd.h>

int gval = 10;

int main(int argc ,char* argv[]){
    pid_t pid;
    int lval = 20;
    gval ++ ,lval+= 5;

    pid = fork();
    if(pid == 0){
        gval++, lval+=2;
    }
    else{
        gval -= 2;
        lval -= 2;
    }

    if(pid == 0){
        printf("Child process gval=%d lval=%d\n", gval, lval);
    }else{
        printf("Parent process gval=%d lval=%d\n", gval, lval);
    }

    return 0;

}