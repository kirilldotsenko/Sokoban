//
// Created by kirill on 12.04.19.
//

#ifndef PROJECT_MAPRECIPIENT_H
#define PROJECT_MAPRECIPIENT_H
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
#include <sys/ioctl.h>

using namespace std;
char message[] = "M";
char message1[]="K";
char buf[1024];
int counter=0;
int bytesAv=0;
int check=0;
char pl1;
char pl2;
char button;
const TCODColor player{200, 200, 200};
const TCODColor wall{0, 255, 0};
const TCODColor boxChar{144, 238, 144};
const TCODColor boxInt{128, 128, 128};
const TCODColor box{255,255,0};
const TCODColor markChar{144, 238, 144};
const TCODColor markInt{128, 128, 128};
const TCODColor mark{255,255,0};
const TCODColor win{255,0,0};
const vector<TCODColor> colourVec = {player, wall, boxChar, boxInt,box,markChar,markInt,mark,win};
vector<int> Player;
vector<int> Player2;
map<Box <char>,vector <int> >O_BoxChar;
map<Box <int>,vector <int> >O_BoxInt;
map<CommonBox,vector<int>>O_Box;
map<Mark <char>,vector <int> >X_MarkChar;
map<Mark <int>,vector <int> >X_MarkInt;
map<CommonMark,vector<int>>X_Mark;

void MapR(){
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3458);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    ofstream file("map.txt");
    send(sock, message, sizeof(message), 0);
    while(true){
        int res;
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
            file.write(buf, res);
            file.close();
        }
        send(sock, message1, sizeof(message1), 0);
        recv(sock,buf, sizeof(buf),0);
        if (buf[0]=='Y'){
            pl1='@';
            pl2='P';
        }
        if (buf[0]=='N'){
            pl1='P';
            pl2='@';
            check++;
        }

        ifstream in("map.txt");
        TwoD<char> TestBoard;
        in >> TestBoard;
        TCODConsole::initRoot(TestBoard.GetDmX(), TestBoard.GetDmY(), "SOKOBAN");
        TestBoard.GameMap(TestBoard, colourVec, Player,Player2, X_MarkChar,X_MarkInt, O_BoxChar,O_BoxInt,TypeBox,X_Mark,O_Box,pl1,pl2);
        while (TestBoard.ifWin(X_MarkChar,X_MarkInt,X_Mark,counter) && EndOfGame(0)) {
            counter = updateWinPositions(X_MarkChar, X_MarkInt, O_BoxChar, O_BoxInt, O_Box, X_Mark, colourVec, pl1,
                                         pl2);
            buf[0]=chkKeyPressAndMovePlayer(TestBoard, Player, colourVec, O_BoxChar, O_BoxInt, O_Box, pl1, pl2,check);
            if ((buf[0]=='W' || buf[0]=='w' || buf[0]=='A' || buf[0]=='a' || buf[0]=='S' || buf[0]=='s' || buf[0]=='D' || buf[0]=='d' || buf[0]=='Q' || buf[0]=='q') && check==0) {
                send(sock, buf, sizeof(buf), 0);
                check++;
            }
            if (!bytesAv && ioctl (sock,FIONREAD,&bytesAv) >= 0)
                continue;
            else
                recv(sock,buf,sizeof(buf),0);
            if(buf[1]=='S'){
                check--;
                bytesAv=0;
            }
            if (buf[0]=='W' || buf[0]=='w' || buf[0]=='A' || buf[0]=='a' || buf[0]=='S' || buf[0]=='s' || buf[0]=='D' || buf[0]=='d' || buf[0]=='Q' || buf[0]=='q'){
                button=buf[0];
                UpdatePlayer2(TestBoard,Player2,colourVec,O_BoxChar,O_BoxInt,O_Box,pl1,pl2,button);
                buf[0]=' ';
            }
        }
    }

    close(sock);
}

#endif //PROJECT_MAPRECIPIENT_H
