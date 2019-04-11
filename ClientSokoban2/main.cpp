#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
char message[] = "Hello there!\n";
char buf[1];
int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3429);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    ofstream file("map.txt", ios::in | ios::trunc | ios::binary);
    send(sock, message, sizeof(message), 0);
    for(int res;;){
        res=recv(sock, buf, sizeof(buf), 0);
        if (res == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                break;
            }
            else
            {
                break;
            }
        }
        if (res == 0)
        {
            break;
        }
        else
        {
            file.write(buf, sizeof(buf));
            cout<<buf<<endl;
        }
    }
    file.close();
    close(sock);
    return 0;
}