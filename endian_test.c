#include<stdio.h>
#include<arpa/inet.h>


int endian_conv();
int endian_addr();
int endian_addrin();
int endian_ntoa();


int main(){
    // endian_conv();
    // endian_addr();
    endian_addrin();

    return 0;
}

int endian_ntoa(){
    sockaddr_in addr_inet;
    addr_inet.sin_addr.s_addr = htonl(0x1020304)

}

int endian_addrin(){
    char *addr1 = "217.0.0.1";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr1, &addr_inet.sin_addr)){
        printf("Conversion error\n");
    }
    else{
        printf("Network ordered  integer addr: %#x\n", addr_inet.sin_addr.s_addr);
    }

    return 0;
}

int endian_conv(){
    unsigned short  host_port = 0x1234;
    unsigned short  net_port;
    unsigned long  host_ipv4 = 0x12345678;
    unsigned long  net_ipv4;

    net_port = htons(host_port);
    net_ipv4 = htonl(host_ipv4);

    printf("host port = %#x\n", host_port);
    printf("net  port = %#x\n", net_port);

    printf("host ipv4 = %#lx\n", host_ipv4);
    printf("net  ipv4 = %#lx\n", net_ipv4);
    return 0;
}

int endian_addr(){
    char *addr1 ="1.2.3.4";
    char *addr2 ="1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr == INADDR_NONE){
        printf("error happend\n");
    }else{
        printf("Network ordered integer addr: %#lx\n",conv_addr);
    }

    unsigned long host_addr = ntohl(conv_addr);
    printf("host ordered integer addr: %#lx\n",host_addr);

    conv_addr = inet_addr(addr2);
    if(conv_addr == INADDR_NONE){
        printf("error happend\n");
    }else{
        printf("Network ordered integer addr: %#lx\n",conv_addr);
    }

    return 0;
}