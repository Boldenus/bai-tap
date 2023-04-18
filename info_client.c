#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000); 

    if (connect(client, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("connect() failed");
        return 1;
    }
        
    char pcName[10];
    int diskNum;
    char diskName[5];
    int diskSize[5];
    char buf[256];
    char buf1[50];

    while (1)
    {
        printf("Nhap thong tin may tinh\n");
        printf("Nhap ten may tinh: ");
        fgets(pcName, sizeof(pcName), stdin);
        pcName[strlen(pcName) - 1] = 0;

        printf("Nhap so o dia: ");
        scanf("%d", &diskNum);
        for(int i=0; i<diskNum; i++){
            printf("Nhap ky tu o %d: ", i+1);
            scanf("%c", &diskName[i]);
            printf("Nhap dung luong:");
            scanf("%d", &diskSize[i]);
            sprintf(buf1," %c-%dGB ", diskName[i], diskSize[i]);
        }

        sprintf(buf,"%s %s", pcName, buf1);
        send(client, buf, strlen(buf), 0);
    }

    // Ket thuc, dong socket
    close(client);

    return 0;
}