#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    DIR *dir;
    struct dirent *ent;
    vector<string> maps;
    if ((dir = opendir("/home/kirill/CLionProjects/ServerSokoban/cmake-build-debug/GameMaps")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                maps.push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
    srand(time(NULL));
    string a = maps[rand() % maps.size()];

    int listener;
    struct sockaddr_in addr;
    char buf[1024];
    char players[]="Y";
    char players1[]="N";
    char control[]="S";
    int bytes_read;
    int count = 0;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        perror("socket");
        exit(1);
    }

    fcntl(listener, F_SETFL, O_NONBLOCK);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3458);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(2);
    }

    listen(listener, 2);

    set<int> clients;
    clients.clear();

    while (1) {
        // Заполняем множество сокетов
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);

        for (set<int>::iterator it = clients.begin(); it != clients.end(); it++)
            FD_SET(*it, &readset);

        // Задаём таймаут
        timeval timeout;
        timeout.tv_sec = 20;
        timeout.tv_usec = 0;

        // Ждём события в одном из сокетов
        int mx = max(listener, *max_element(clients.begin(), clients.end()));
        if (select(mx + 1, &readset, NULL, NULL, &timeout) <= 0) {
            perror("select");
            exit(3);
        }

        // Определяем тип события и выполняем соответствующие действия
        if (FD_ISSET(listener, &readset)) {
            // Поступил новый запрос на соединение, используем accept
            int sock = accept(listener, NULL, NULL);
            if (sock < 0) {
                perror("accept");
                exit(3);
            }

            fcntl(sock, F_SETFL, O_NONBLOCK);

            clients.insert(sock);
        }

        for (set<int>::iterator it = clients.begin(); it != clients.end(); it++) {
            if (FD_ISSET(*it, &readset)) {
                // Поступили данные от клиента, читаем их
                bytes_read = recv(*it, buf, 1024, 0);


                if (bytes_read <= 0) {
                    // Соединение разорвано, удаляем сокет из множества
                    close(*it);
                    clients.erase(*it);
                    continue;
                }

                // Отправляем данные обратно клиенту

                if (buf[0] == 'M') {
                    size_t length = 0;
                    char *buff = 0;
                    ifstream fs("/home/kirill/CLionProjects/ServerSokoban/cmake-build-debug/GameMaps/" + a,
                                ios::out | ios::binary);
                    if (fs.is_open()) {
                        fs.seekg(0, ios::end);
                        length = fs.tellg();
                        fs.seekg(0, ios::beg);
                        buff = new char[1 + length];
                        fs.read(buff, length);
                        buff[length] = 0;
                    }
                    send(*it, buff, length, 0);
                    fs.close();
                }
                if(buf[0]=='K'){
                    if(count==0) {
                        send(*it, players, sizeof(players), 0);
                        count++;
                    }
                    else{
                        send(*it, players1, sizeof(players1), 0);
                        count--;
                    }
                }
                if(clients.size()==2 && (buf[0]=='W' || buf[0]=='w' || buf[0]=='A' || buf[0]=='a' || buf[0]=='S' || buf[0]=='s' || buf[0]=='D' || buf[0]=='d' || buf[0]=='Q' || buf[0]=='q')){
                    if(it==clients.begin()){
                        buf[1]='S';
                        send(*it+1,buf,sizeof(buf),0);
                    }
                    else{
                        buf[1]='S';
                        send(*it-1,buf,sizeof(buf),0);
                    }
                }
            }
        }
    }

}