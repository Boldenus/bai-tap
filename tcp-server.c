#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server == -1){
        printf("false to creat socket: %d - %s\n", errno, strerror(errno));
        exit(1);
    }
    else{
        printf("socket created!\n");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(argv[1]));

    int  bin = bind(server, (struct sockaddr*)&addr, sizeof(addr));
    
    if(bin == -1){
        printf("bind() false\n");
        exit(1);
    }
    else{
        printf("bind() success\n");
    }

    if(listen(server, 5)){
        printf("listen() false\n");
        exit(1);
    }

    int client = accept(server, NULL, NULL);
    if(client == -1){
        printf("can't access client\n");
        exit(1);
    }
    
    FILE* f = fopen(argv[2], "rb");
    char buf[1000];
    while (!feof(f))
    {
        int read_1 = fread(buf, 1, sizeof(buf), f);
    }
    
    send(client, buf, sizeof(buf), 0);

    char buf1[256];
    int ret = recv(client, buf1, sizeof(buf1), 0);
    if (ret <= 0)
    {
        printf("recv() failed.\n");
        exit(1);
    }
    else{
        buf1[ret] = 0;
        printf("%s",buf1);
    }
    
    FILE* f2 = fopen(argv[3], "wb");
    fwrite(buf1, 1, sizeof(buf1), f2);

    close(client);
    close(server);

    return 0;  
}