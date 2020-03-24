#include"mysocket.h"

int main(int argc, char* argv[]){
    struct iovec vec[2];

    char buffer1[] = "ABCDEFG";  
    char buffer2[] = "1234567";

    vec[0].iov_base = buffer1;
    vec[0].iov_len  = 4;
    vec[1].iov_base = buffer2;
    vec[1].iov_len  = 3;

    int str_len = writev(1, vec, 2);
    printf("write len;%d\n",str_len);
    return 0;
}