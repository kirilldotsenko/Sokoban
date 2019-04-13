//
// Created by kirill on 25.03.19.
//

#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <libtcod.hpp>
#include <boost/any.hpp>
using namespace std;

class CommonBox{
private:
    int i;
    int j;
    char sym;
public:
    CommonBox()=default;
    CommonBox(int value,int value1,char value3){
        j=value;
        i=value1;
        sym=value3;
    }
    char typ()
    const{
        return sym;
    }
    bool operator<( const CommonBox& other) const
    {
        if ( j == other.j )
        {
            return i < other.i;
        }

        return j < other.j;
    }
};

class CommonMark{
private:
    int i;
    int j;
    char sym;
public:
    CommonMark()=default;
    CommonMark(int value,int value1,char value3){
        j=value;
        i=value1;
        sym=value3;
    }
    char typ()
    const{
        return sym;
    }
    bool operator<( const CommonMark& other) const
    {
        if ( j == other.j )
        {
            return i < other.i;
        }

        return j < other.j;
    }
};

template <typename K>
class Box{
private:
    K a;
    int i;
    int j;
    char sym;
public:
    Box()=default;
    Box(int value,int value1,char value3){
        j=value;
        i=value1;
        sym=value3;
    }
    char typ()
    const{
        if(typeid(a)==typeid(char))
            return 'C';
        else
            return 'I';
    }
    bool operator<( const Box& other) const
    {
        if ( j == other.j )
        {
            return i < other.i;
        }

        return j < other.j;
    }


};

template<typename D>
class Mark{
private:
    D a;
    int i;
    int j;
    char sym;
public:
    Mark()=default;
    Mark(int value,int value1,char value2){
        j=value;
        i=value1;
        sym=value2;
    }
    char typ()
    const{
        if (typeid(a) == typeid(char))
            return 'C';
        else
            return 'I';
    }
    bool operator<( const Mark& other) const
    {
        if ( j == other.j )
        {
            return i < other.i;
        }

        return j < other.j;
    }


};


template <typename T> class TwoD{

public:
    TwoD()=default;
    TwoD(const unsigned argLen,const unsigned argWth):length(argLen),width(argWth){
        val=new T *[length];
        for (auto i=0;i<length;i++)
            val[i]=new T[width];
    }
    ~TwoD() {}
    void SetPos(const unsigned posX, const unsigned posY, T obj) {
        val[posX][posY] = obj;
    }
    char GetPos (const unsigned posX, const unsigned posY)
    const{
        return val[posX][posY];
    }

    unsigned  GetDmX()
    const {
        return width;
    }

    unsigned  GetDmY()
    const {
        return length;
    }
    void GameMap(TwoD<char>TwoDArray,const vector<TCODColor>& colourVec, vector<int>& Player,vector<int>&Player2, map<Mark <char>,vector <int>>& X_MarkChar,map<Mark <int>,vector <int>>& X_MarkInt,map<Box<char>,
            vector<int>>& O_BoxChar,map<Box <int>, vector<int>>& O_BoxInt,map<vector<int>,int>&TypeBox,map<CommonMark,vector<int>>&X_Mark,map<CommonBox,vector<int>>&O_Box,char pl1,char pl2){
        TCODConsole::initRoot(TwoDArray.GetDmX(), TwoDArray.GetDmY(), "SOKOBAN");
        TCODConsole::root->setDefaultBackground({220,220,220});
        for (auto i = 0; i < TwoDArray.GetDmY(); i++){
            for (auto j = 0; j < TwoDArray.GetDmX(); j++){
                TCODConsole::root -> setChar(j, i, TwoDArray.GetPos(i,j));
            }
        }
        for (auto i = 0; i < TwoDArray.GetDmY(); i++){
            for (auto j = 0; j < TwoDArray.GetDmX(); j++) {

                if (TCODConsole::root->getChar(j, i) == pl1) {
                    TCODConsole::root->setCharBackground(j, i, colourVec[0]);
                    Player = {j, i};
                }else if(TCODConsole::root->getChar(j,i)==pl2){
                    TCODConsole::root->setCharBackground(j, i, colourVec[0]);
                    Player2 = {j, i};
                }
                else if (TCODConsole::root->getChar(j, i) == '#') {
                    TCODConsole::root->setCharBackground(j, i, colourVec[1]);
                } else if (TCODConsole::root->getChar(j, i) == 'O') {
                    for (auto &cross:TypeBox) {
                        if (cross.first[0] == j && cross.first[1] == i && cross.second == 1) {
                            TCODConsole::root->setCharBackground(j, i, colourVec[2]);
                            Box<char> BoxChar1(j, i, 'O');
                            O_BoxChar[BoxChar1] = {j, i};
                        } else if (cross.first[0] == j && cross.first[1] == i && cross.second == 2) {
                            TCODConsole::root->setCharBackground(j, i, colourVec[3]);
                            Box<int> BoxInt1(j, i, '0');
                            O_BoxInt[BoxInt1] = {j, i};
                        } else if(cross.first[0] == j && cross.first[1] == i && cross.second == 0) {
                            TCODConsole::root->setCharBackground(j, i, colourVec[4]);
                            CommonBox CBox(j,i,'A');
                            O_Box[CBox] = {j, i};
                        }
                    }
                } else if (TCODConsole::root->getChar(j, i) == 'X') {
                    for (auto &cross:TypeBox) {
                        if (cross.first[0] == j && cross.first[1] == i && cross.second == 1) {
                            TCODConsole::root->setCharBackground(j, i, colourVec[5]);
                            Mark<char> MarkChar1(j, i, 'X');
                            X_MarkChar[MarkChar1] = {j, i};
                        } else if (cross.first[0] == j && cross.first[1] == i && cross.second == 2) {
                            TCODConsole::root->setCharBackground(j, i, colourVec[6]);
                            Mark<int> MarkInt1(j, i, 'X');
                            X_MarkInt[MarkInt1] = {j, i};
                        } else if(cross.first[0] == j && cross.first[1] == i && cross.second == 0){
                            TCODConsole::root->setCharBackground(j, i, colourVec[7]);
                            CommonMark CMark(j,i,'A');
                            X_Mark[CMark] = {j, i};
                        }
                    }
                }
            }
        }
        TCODConsole::root->flush();
    }
    bool ifWin(map<Mark <char>,vector<int>>& X_MarkChar,map<Mark <int>,vector<int>>& X_MarkInt,map<CommonMark,vector<int>>&X_Mark,int counter){
        int winCnt = 0;
        for (auto cross : X_MarkChar){
            winCnt++;
        }
        for (auto cross : X_MarkInt){
            winCnt++;
        }
        for (auto cross : X_Mark){
            winCnt++;
        }
        if (winCnt == counter) {
            return false;
        }
        else{
            return true;
        }
    }


private:
    unsigned length;
    unsigned width;
    T **val;

};
#endif //PROJECT_BOARD_H
