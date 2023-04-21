#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    

    int sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sk == -1)
    {
        printf("false to create socket!!!: %d - %s\n", errno, strerror(errno));
    }
    else{
        printf("socket created!");
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    int res = connect(sk, (struct sockaddr *)&addr, sizeof(addr));
    if(res == -1){
        printf("connect false %s \n", strerror(errno));
        return 1;
    }
    else{
        printf("success\n");
    }
    
    char mes[200];
    printf("enter your message: ");
    fgets(mes, sizeof(mes), stdin);
    char* str = mes;
    send(sk, str, strlen(str), 0);

    char getmes[2000];
    int get = recv(sk, getmes, sizeof(getmes), 0);
    getmes[get] = 0;
    printf("data received:%s\n", getmes);

    close(sk);

    return 0;
}