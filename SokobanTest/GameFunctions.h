//
// Created by kirill on 27.03.19.
//

#ifndef PROJECT_GAMEFUNCTIONS_H
#define PROJECT_GAMEFUNCTIONS_H
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <libtcod.hpp>
#include "cmake-build-debug/Board.h"
int i=1;
map<vector<int>,int>TypeBox;
ostream& operator<<(ostream& stream, TwoD<char>& TwoDArray) {
    for (auto i = 0; i < TwoDArray.GetDmY(); i++){
        for (auto j = 0; j < TwoDArray.GetDmX(); j++){
            stream << TwoDArray.GetPos(i,j);
        }
        cout << endl;
    }
    return stream;
}

ifstream& operator>>(ifstream &file, TwoD<char> &TwoDArray) {
    unsigned len, wth;
    int x,y,typ;
    file >>len >> wth;
    TwoD<char> mapLocal(len, wth);
    TwoDArray = mapLocal;
    string buf;
    getline(file,buf);
    for (auto i = 0; i < len ; i++){
        for (auto j = 0; j <= wth; j++){
            TwoDArray.SetPos(i,j,file.get());
        }
    }
    while(getline(file,buf)){
        file >> x >> y >> typ;
        TypeBox[{x, y}] = typ;
    }

}
bool EndOfGame(int a){
    i+=a;
    if(i==1)
        return true;
    else
        return false;
}

int updateWinPositions(map<Mark <char>,vector<int>>& X_MarkChar,map<Mark <int> ,vector<int>>& X_MarkInt,map<Box<char>, vector<int>>& O_BoxChar,map<Box<int>, vector<int>>& O_BoxInt,
        map<CommonBox,vector<int>>&O_Box,map<CommonMark,vector<int>>&X_Mark,const vector<TCODColor>& colourVec,char pl1,char pl2) {
    int counter=0;
    for (auto &cross : X_MarkChar) {
        for(auto &cross1:O_BoxChar) {
            if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == 'X') {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[5]);
            } else if ((TCODConsole::root->getChar(cross.second[0], cross.second[1]) == 'O') && (cross.second[0]==cross1.second[0]) && (cross.second[1]==cross1.second[1]) && (cross.first.typ()==cross1.first.typ())) {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[8]);
                counter++;
            } else if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == pl1) {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[0]);
            } else if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == ' ') {
                TCODConsole::root->setChar(cross.second[0], cross.second[1], 'X');
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[5]);
            }
        }
    }
    for (auto &cross : X_MarkInt) {
        for(auto &cross1:O_BoxInt) {
            if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == 'X') {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[6]);
            } else if ((TCODConsole::root->getChar(cross.second[0], cross.second[1]) == 'O') && (cross.second[0]==cross1.second[0]) && (cross.second[1]==cross1.second[1]) && (cross.first.typ()==cross1.first.typ())) {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[8]);
                counter++;
            } else if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == pl1) {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[0]);
            } else if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == ' ') {
                TCODConsole::root->setChar(cross.second[0], cross.second[1], 'X');
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[6]);
            }
        }
    }
    for(auto &cross:X_Mark){
        for(auto &cross1:O_Box){
            if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == 'X') {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[7]);
            }else if((TCODConsole::root->getChar(cross.second[0], cross.second[1]) == 'O') && (cross.second[0]==cross1.second[0]) && (cross.second[1]==cross1.second[1]) && (cross.first.typ()==cross1.first.typ())){
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[8]);
                counter++;
            }else if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == pl1) {
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[0]);
            } else if (TCODConsole::root->getChar(cross.second[0], cross.second[1]) == ' ') {
                TCODConsole::root->setChar(cross.second[0], cross.second[1], 'X');
                TCODConsole::root->setCharBackground(cross.second[0], cross.second[1], colourVec[7]);
            }
        }
    }
    return counter;
}

void chkKeyPressAndMovePlayer(TwoD<char>TwoDArray,vector<int>& Player, const vector<TCODColor>& colourVec,map<Box<char>, vector<int>>& O_BoxChar,map<Box<int>, vector<int>>& O_BoxInt,map<CommonBox,vector<int>>&O_Box,char pl1,char pl2){
    TCOD_key_t key = TCODConsole::checkForKeypress();
    TCODConsole::root->flush();

    if ( key.c == 'w' || key.c == 'W' ) {
        if (TCODConsole::root -> getChar(Player[0], Player[1] - 1) != '#' && TCODConsole::root -> getChar(Player[0], Player[1] - 1) != pl2) {
            if (TCODConsole::root->getChar(Player[0], Player[1] - 1) != 'O' && Player[1]-1>=0) {
                TCODConsole::root->setChar(Player[0], Player[1] - 1, pl1);
                TCODConsole::root->setCharBackground(Player[0], Player[1] - 1, colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                Player = {Player[0], Player[1] - 1};
            }else if((TCODConsole::root -> getChar(Player[0], TwoDArray.GetDmY()-1) != '#')
            && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-1) != 'O')
            && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-1) != pl2)
            && Player[1]-1<0){
                TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-1, pl1);
                TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-1, colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                Player={Player[0],Player[1]=TwoDArray.GetDmY()-1};
            }else if ((TCODConsole::root->getChar(Player[0], Player[1] - 1) == 'O')
                       && (TCODConsole::root->getChar(Player[0], Player[1] - 2) != '#')
                       && (TCODConsole::root->getChar(Player[0], Player[1] - 2) != pl2)
                       && (TCODConsole::root->getChar(Player[0], Player[1] - 2) != 'O')
                       && Player[1]-2>=0) {
                TCODConsole::root->setChar(Player[0], Player[1] - 1, pl1);
                TCODConsole::root->setCharBackground(Player[0], Player[1] - 1, colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]==cross.second[0])&&(Player[1]-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], Player[1] - 2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], Player[1] - 2, colourVec[2]);
                        cross.second={cross.second[0],cross.second[1]-1};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]==cross.second[0])&&(Player[1]-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], Player[1] - 2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], Player[1] - 2, colourVec[3]);
                        cross.second={cross.second[0],cross.second[1]-1};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]==cross.second[0])&&(Player[1]-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], Player[1] - 2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], Player[1] - 2, colourVec[4]);
                        cross.second={cross.second[0],cross.second[1]-1};
                    }
                }
                Player = {Player[0], Player[1] - 1};
            }else if ((TCODConsole::root->getChar(Player[0], Player[1] - 1) == 'O')
                      && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-1) != '#')
                      && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-1) != pl2)
                      && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-1) != 'O')
                      && Player[1]-2<0) {
                TCODConsole::root->setChar(Player[0], Player[1] - 1, pl1);
                TCODConsole::root->setCharBackground(Player[0], Player[1] - 1, colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]==cross.second[0])&&(Player[1]-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-1, 'O');
                        TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-1, colourVec[2]);
                        cross.second={cross.second[0],cross.second[1]=TwoDArray.GetDmY()-1};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]==cross.second[0])&&(Player[1]-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-1, 'O');
                        TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-1, colourVec[3]);
                        cross.second={cross.second[0],cross.second[1]=TwoDArray.GetDmY()-1};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]==cross.second[0])&&(Player[1]-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-1, 'O');
                        TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-1, colourVec[4]);
                        cross.second={cross.second[0],cross.second[1]=TwoDArray.GetDmY()-1};
                    }
                }
                Player = {Player[0], Player[1] - 1};
            }else if ((TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-1) == 'O')
                      && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-2) != '#')
                      && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY()-2) != pl2)
                      && (TCODConsole::root->getChar(Player[0], TwoDArray.GetDmY() - 2) != 'O')
                      && Player[1]-1<0){
                TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-1, pl1);
                TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY() - 1, colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]==cross.second[0])&&(TwoDArray.GetDmY()-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-2, colourVec[2]);
                        cross.second={cross.second[0],cross.second[1]=TwoDArray.GetDmY()-2};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]==cross.second[0])&&(TwoDArray.GetDmY()-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-2, colourVec[3]);
                        cross.second={cross.second[0],cross.second[1]=TwoDArray.GetDmY()-2};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]==cross.second[0])&&(TwoDArray.GetDmY()-1==cross.second[1])){
                        TCODConsole::root->setChar(Player[0], TwoDArray.GetDmY()-2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], TwoDArray.GetDmY()-2, colourVec[4]);
                        cross.second={cross.second[0],cross.second[1]=TwoDArray.GetDmY()-2};
                    }
                }
                Player = {Player[0], Player[1]=TwoDArray.GetDmY()-1};
            }
        }
        TCODConsole::root->flush();
    }
    else if ( key.c == 'a' || key.c == 'A' ) {
        if (TCODConsole::root -> getChar(Player[0] - 1, Player[1]) != '#' && TCODConsole::root -> getChar(Player[0] - 1, Player[1]) != 'P') {
            if (TCODConsole::root->getChar(Player[0] - 1, Player[1]) != 'O' && Player[0] - 1 >= 0) {
                TCODConsole::root->setChar(Player[0] - 1, Player[1], pl1);
                TCODConsole::root->setCharBackground(Player[0] - 1, Player[1], colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                Player = {Player[0] - 1, Player[1]};
            } else if ((TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) != '#')
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) != 'O')
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) != pl2)
                       && Player[0] - 1 < 0) {
                TCODConsole::root->setChar(TwoDArray.GetDmX() - 1, Player[1], pl1);
                TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 1, Player[1], colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                Player = {Player[0] = TwoDArray.GetDmX() - 1, Player[1]};
            } else if ((TCODConsole::root->getChar(Player[0] - 1, Player[1]) == 'O')
                       && (TCODConsole::root->getChar(Player[0] - 2, Player[1]) != '#')
                       && (TCODConsole::root->getChar(Player[0] - 2, Player[1]) != pl2)
                       && (TCODConsole::root->getChar(Player[0] - 2, Player[1]) != 'O')
                       && Player[0] - 2 >= 0) {
                TCODConsole::root->setChar(Player[0] - 1, Player[1], pl1);
                TCODConsole::root->setCharBackground(Player[0] - 1, Player[1], colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                for (auto &cross:O_BoxChar) {
                    if ((Player[0] - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(Player[0] - 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(Player[0] - 2, Player[1], colourVec[2]);
                        cross.second = {cross.second[0] - 1, cross.second[1]};
                    }
                }
                for (auto &cross:O_BoxInt) {
                    if ((Player[0] - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(Player[0] - 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(Player[0] - 2, Player[1], colourVec[3]);
                        cross.second = {cross.second[0] - 1, cross.second[1]};
                    }
                }
                for (auto &cross:O_Box) {
                    if ((Player[0] - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(Player[0] - 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(Player[0] - 2, Player[1], colourVec[4]);
                        cross.second = {cross.second[0] - 1, cross.second[1]};
                    }
                }
                Player = {Player[0] - 1, Player[1]};
            } else if ((TCODConsole::root->getChar(Player[0] - 1, Player[1]) == 'O')
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) != '#')
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) != pl2)
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) != 'O')
                       && Player[0] - 2 < 0) {
                TCODConsole::root->setChar(Player[0] - 1, Player[1], pl1);
                TCODConsole::root->setCharBackground(Player[0] - 1, Player[1], colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                for (auto &cross:O_BoxChar) {
                    if ((Player[0] - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(TwoDArray.GetDmX() - 1, Player[1], 'O');
                        TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 1, Player[1], colourVec[2]);
                        cross.second = {cross.second[0] = TwoDArray.GetDmX() - 1, cross.second[1]};
                    }
                }
                for (auto &cross:O_BoxInt) {
                    if ((Player[0] - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(TwoDArray.GetDmX() - 1, Player[1], 'O');
                        TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 1, Player[1], colourVec[3]);
                        cross.second = {cross.second[0] = TwoDArray.GetDmX() - 1, cross.second[1]};
                    }
                }
                for (auto &cross:O_Box) {
                    if ((Player[0] - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(TwoDArray.GetDmX() - 1, Player[1], 'O');
                        TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 1, Player[1], colourVec[4]);
                        cross.second = {cross.second[0] = TwoDArray.GetDmX() - 1, cross.second[1]};
                    }
                }
                Player = {Player[0] - 1, Player[1]};
            } else if ((TCODConsole::root->getChar(TwoDArray.GetDmX() - 1, Player[1]) == 'O')
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 2, Player[1]) != '#')
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 2, Player[1]) != pl2)
                       && (TCODConsole::root->getChar(TwoDArray.GetDmX() - 2, Player[1]) != 'O')
                       && Player[0] - 1 < 0) {
                TCODConsole::root->setChar(TwoDArray.GetDmX() - 1, Player[1], pl1);
                TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 1, Player[1], colourVec[0]);
                TCODConsole::root->setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1], {0, 0, 0});
                for (auto &cross:O_BoxChar) {
                    if ((TwoDArray.GetDmX() - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(TwoDArray.GetDmX() - 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 2, Player[1], colourVec[2]);
                        cross.second = {cross.second[0] = TwoDArray.GetDmX() - 2, cross.second[1]};
                    }
                }
                for (auto &cross:O_BoxInt) {
                    if ((TwoDArray.GetDmX() - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(TwoDArray.GetDmX() - 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 2, Player[1], colourVec[3]);
                        cross.second = {cross.second[0] = TwoDArray.GetDmX() - 2, cross.second[1]};
                    }
                }
                for (auto &cross:O_Box) {
                    if ((TwoDArray.GetDmX() - 1 == cross.second[0]) && (Player[1] == cross.second[1])) {
                        TCODConsole::root->setChar(TwoDArray.GetDmX() - 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(TwoDArray.GetDmX() - 2, Player[1], colourVec[4]);
                        cross.second = {cross.second[0] = TwoDArray.GetDmX() - 2, cross.second[1]};
                    }
                }
                Player = {Player[0] = TwoDArray.GetDmX() - 1, Player[1]};
            }
        }
        TCODConsole::root->flush();
    }
    else if ( key.c == 's' || key.c == 'S' ) {
        if (TCODConsole::root -> getChar(Player[0], Player[1] + 1) != '#' && TCODConsole::root -> getChar(Player[0], Player[1] + 1) != pl2){
            if (TCODConsole::root -> getChar(Player[0], Player[1] + 1) != 'O' && Player[1]+1<TwoDArray.GetDmY()){
                TCODConsole::root -> setChar(Player[0], Player[1] + 1, pl1);
                TCODConsole::root->setCharBackground(Player[0], Player[1] + 1,colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                Player = {Player[0], Player[1] + 1};
            }
            else if((TCODConsole::root -> getChar(Player[0], 0) != '#') && (TCODConsole::root -> getChar(Player[0], 0)!='O')&& (TCODConsole::root -> getChar(Player[0], 0)!=pl2) && (Player[1]+1>=TwoDArray.GetDmY())){
                TCODConsole::root -> setChar(Player[0], 0, pl1);
                TCODConsole::root->setCharBackground(Player[0], 0,colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                Player = {Player[0], Player[1]=0};
            }
            else if ((TCODConsole::root -> getChar(Player[0], Player[1] + 1) == 'O')
                     && (TCODConsole::root -> getChar(Player[0], Player[1] + 2) != '#')
                     && (TCODConsole::root -> getChar(Player[0], Player[1] + 2) != pl2)
                     && (TCODConsole::root -> getChar(Player[0], Player[1] + 2) != 'O')
                     && Player[1]+2<TwoDArray.GetDmY()){
                TCODConsole::root -> setChar(Player[0], Player[1] + 1, pl1);
                TCODConsole::root->setCharBackground(Player[0], Player[1] + 1,colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]==cross.second[0])&&(Player[1]+1==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], Player[1] + 2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], Player[1] + 2,colourVec[2]);
                        cross.second={cross.second[0],cross.second[1]+1};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]==cross.second[0])&&(Player[1]+1==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], Player[1] + 2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], Player[1] + 2,colourVec[3]);
                        cross.second={cross.second[0],cross.second[1]+1};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]==cross.second[0])&&(Player[1]+1==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], Player[1] + 2, 'O');
                        TCODConsole::root->setCharBackground(Player[0], Player[1] + 2,colourVec[4]);
                        cross.second={cross.second[0],cross.second[1]+1};
                    }
                }
                Player = {Player[0], Player[1] + 1};
            }
            else if ((TCODConsole::root -> getChar(Player[0], Player[1] + 1) == 'O')
                     && (TCODConsole::root -> getChar(Player[0], 0) != '#')
                     && (TCODConsole::root -> getChar(Player[0], 0) != pl2)
                     && (TCODConsole::root -> getChar(Player[0], 0) != 'O')
                     && Player[1]+2>=TwoDArray.GetDmY()){
                TCODConsole::root -> setChar(Player[0], Player[1]+1, pl1);
                TCODConsole::root->setCharBackground(Player[0], Player[1]+1,colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]==cross.second[0])&&(Player[1]+1==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], 0 , 'O');
                        TCODConsole::root->setCharBackground(Player[0], 0 ,colourVec[2]);
                        cross.second={cross.second[0],cross.second[1]=0};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]==cross.second[0])&&(Player[1]+1==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], 0 , 'O');
                        TCODConsole::root->setCharBackground(Player[0], 0 ,colourVec[3]);
                        cross.second={cross.second[0],cross.second[1]=0};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]==cross.second[0])&&(Player[1]+1==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], 0 , 'O');
                        TCODConsole::root->setCharBackground(Player[0], 0 ,colourVec[4]);
                        cross.second={cross.second[0],cross.second[1]=0};
                    }
                }
                Player = {Player[0], Player[1] + 1};
            }
            else if ((TCODConsole::root->getChar(Player[0], 0) == 'O')
                     && (TCODConsole::root->getChar(Player[0], 1) != '#')
                     && (TCODConsole::root->getChar(Player[0], 1) != pl2)
                     && (TCODConsole::root->getChar(Player[0], 1) != 'O')
                     && Player[1] + 1 >= TwoDArray.GetDmY()) {
                TCODConsole::root -> setChar(Player[0], 0, pl1);
                TCODConsole::root->setCharBackground(Player[0], 0,colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]==cross.second[0])&&(0==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], 1 , 'O');
                        TCODConsole::root->setCharBackground(Player[0], 1 ,colourVec[2]);
                        cross.second={cross.second[0],cross.second[1]=1};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]==cross.second[0])&&(0==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], 1 , 'O');
                        TCODConsole::root->setCharBackground(Player[0], 1 ,colourVec[3]);
                        cross.second={cross.second[0],cross.second[1]=1};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]==cross.second[0])&&(0==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0], 1 , 'O');
                        TCODConsole::root->setCharBackground(Player[0], 1 ,colourVec[4]);
                        cross.second={cross.second[0],cross.second[1]=1};
                    }
                }
                Player = {Player[0], Player[1]=0};
            }
        }
        TCODConsole::root->flush();
    }
    else if ( key.c == 'd' || key.c == 'D' ) {
        if (TCODConsole::root -> getChar(Player[0] + 1, Player[1]) != '#' && TCODConsole::root -> getChar(Player[0] + 1, Player[1]) != pl2){
            if (TCODConsole::root -> getChar(Player[0]+1, Player[1]) != 'O' && Player[0]+1<TwoDArray.GetDmX()){
                TCODConsole::root -> setChar(Player[0]+1, Player[1], pl1);
                TCODConsole::root->setCharBackground(Player[0]+1, Player[1],colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                Player = {Player[0]+1, Player[1]};
            }
            else if((TCODConsole::root -> getChar(0, Player[1]) != '#') && (TCODConsole::root -> getChar(0, Player[1])!='O') && (TCODConsole::root -> getChar(0, Player[1])!=pl2) && (Player[0]+1>=TwoDArray.GetDmX())){
                TCODConsole::root -> setChar(0, Player[1], pl1);
                TCODConsole::root->setCharBackground(0, Player[1],colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                Player = {Player[0]=0, Player[1]};
            }

            else if ((TCODConsole::root -> getChar(Player[0]+1, Player[1]) == 'O')
                     && (TCODConsole::root -> getChar(Player[0]+2, Player[1]) != '#')
                     && (TCODConsole::root -> getChar(Player[0]+2, Player[1]) != pl2)
                     && (TCODConsole::root -> getChar(Player[0]+2, Player[1]) != 'O')
                     && Player[0]+2<TwoDArray.GetDmX()){
                TCODConsole::root -> setChar(Player[0]+1, Player[1], pl1);
                TCODConsole::root->setCharBackground(Player[0]+1, Player[1],colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                for(auto &cross:O_BoxChar){
                    if((Player[0]+1==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0] + 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(Player[0]+2, Player[1],colourVec[2]);
                        cross.second={cross.second[0]+1,cross.second[1]};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]+1==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0] + 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(Player[0]+2, Player[1],colourVec[3]);
                        cross.second={cross.second[0]+1,cross.second[1]};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]+1==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(Player[0] + 2, Player[1], 'O');
                        TCODConsole::root->setCharBackground(Player[0]+2, Player[1],colourVec[4]);
                        cross.second={cross.second[0]+1,cross.second[1]};
                    }
                }
                Player = {Player[0]+1, Player[1]};
            }
            else if ((TCODConsole::root -> getChar(Player[0]+1, Player[1]) == 'O')
                     && (TCODConsole::root -> getChar(0, Player[1]) != '#')
                     && (TCODConsole::root -> getChar(0, Player[1]) != pl2)
                     && (TCODConsole::root -> getChar(0, Player[1]) != 'O')
                     && Player[0]+2>=TwoDArray.GetDmX()){
                TCODConsole::root -> setChar(Player[0]+1, Player[1], pl1);
                TCODConsole::root->setCharBackground(Player[0]+1, Player[1],colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                TCODConsole::root -> setChar(0, Player[1] , 'O');
                TCODConsole::root->setCharBackground(0, Player[1] ,colourVec[2]);
                for(auto &cross:O_BoxChar){
                    if((Player[0]+1==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(0, Player[1] , 'O');
                        TCODConsole::root->setCharBackground(0, Player[1] ,colourVec[2]);
                        cross.second={cross.second[0]=0,cross.second[1]};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((Player[0]+1==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(0, Player[1] , 'O');
                        TCODConsole::root->setCharBackground(0, Player[1] ,colourVec[3]);
                        cross.second={cross.second[0]=0,cross.second[1]};
                    }
                }
                for(auto &cross:O_Box){
                    if((Player[0]+1==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(0, Player[1] , 'O');
                        TCODConsole::root->setCharBackground(0, Player[1] ,colourVec[4]);
                        cross.second={cross.second[0]=0,cross.second[1]};
                    }
                }
                Player = {Player[0]+1, Player[1]};
            }
            else if ((TCODConsole::root->getChar(0, Player[1]) == 'O')
                     && (TCODConsole::root->getChar(1, Player[1]) != '#')
                     && (TCODConsole::root->getChar(1, Player[1]) != pl2)
                     && (TCODConsole::root->getChar(1, Player[1]) != 'O')
                     && Player[0] + 1 >= TwoDArray.GetDmX()) {
                TCODConsole::root -> setChar(0, Player[1], pl1);
                TCODConsole::root->setCharBackground(0, Player[1],colourVec[0]);
                TCODConsole::root-> setChar(Player[0], Player[1], ' ');
                TCODConsole::root->setCharBackground(Player[0], Player[1],{0,0,0});
                for(auto &cross:O_BoxChar){
                    if((0==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(1, Player[1] , 'O');
                        TCODConsole::root->setCharBackground(1, Player[1] ,colourVec[2]);
                        cross.second={cross.second[0]=1,cross.second[1]};
                    }
                }
                for(auto &cross:O_BoxInt){
                    if((0==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(1, Player[1] , 'O');
                        TCODConsole::root->setCharBackground(1, Player[1] ,colourVec[3]);
                        cross.second={cross.second[0]=1,cross.second[1]};
                    }
                }
                for(auto &cross:O_Box){
                    if((0==cross.second[0])&&(Player[1]==cross.second[1])){
                        TCODConsole::root -> setChar(1, Player[1] , 'O');
                        TCODConsole::root->setCharBackground(1, Player[1] ,colourVec[4]);
                        cross.second={cross.second[0]=1,cross.second[1]};
                    }
                }
                Player = {Player[0]=0, Player[1]};
            }
        }
        TCODConsole::root->flush();
    }
    else if(key.c=='q' || key.c=='Q'){
        i+=1;
    }
}
#endif //PROJECT_GAMEFUNCTIONS_H
