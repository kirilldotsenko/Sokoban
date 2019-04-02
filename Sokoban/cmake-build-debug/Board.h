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
    int typ(){
        if(typeid(a)==typeid(char))
            return 'C';
        else
            return 'I';
    }
    int posY(){
        return i;
    }
    int posX() {
        return j;
    }
    char symb() {
        return sym;
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
    int typ() {
        if (typeid(a) == typeid(char))
            return 'C';
        else
            return 'I';
    }
    int posY(){
        return i;
    }
    int posX(){
        return j;
    }
    char symb(char b){
        sym=b;
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
    void GameMap(TwoD<char>TwoDArray,const vector<TCODColor>& colourVec, vector<int>& Player, map<vector<int>,Mark<char> >& X_MarkChar,map<vector<int>,Mark<int> >& X_MarkInt,map<Box<char>, vector<int>>& O_BoxChar,map<Box <int>, vector<int>>& O_BoxInt){
        TCODConsole::initRoot(TwoDArray.GetDmX(), TwoDArray.GetDmY(), "SOKOBAN");
        TCODConsole::root->setDefaultBackground({220,220,220});
        for (auto i = 0; i < TwoDArray.GetDmY(); i++){
            for (auto j = 0; j < TwoDArray.GetDmX(); j++){
                TCODConsole::root -> setChar(j, i, TwoDArray.GetPos(i,j));
            }
        }
        for (auto i = 0; i < TwoDArray.GetDmY(); i++){
            for (auto j = 0; j < TwoDArray.GetDmX(); j++){

                if (TCODConsole::root -> getChar(j, i) == '@'){
                    TCODConsole::root->setCharBackground(j,i,colourVec[0]);
                    Player = {j,i};
                }
                else if (TCODConsole::root -> getChar(j, i) == '#'){
                    TCODConsole::root->setCharBackground(j,i,colourVec[1]);
                }
                else if (TCODConsole::root -> getChar(j, i) == 'O'){

                    TCODConsole::root->setCharBackground(j,i,colourVec[2]);
                    if(count%2==0){
                        Box<char>BoxChar1(j,i,'O');
                        //TCODConsole::root -> setChar(j, i, BoxChar1.symb());
                        //TCODConsole::root->setChar(j,i,'O');
                        //TCODConsole::root->setCharBackground(j,i,colourVec[2]);
                        O_BoxChar[BoxChar1] = {j,i};
                        count++;
                    } else{
                        Box<int>BoxInt1(j,i,'0');
                        //TCODConsole::root -> setChar(j, i, BoxInt1.symb());
                        //TCODConsole::root->setCharBackground(j,i,colourVec[2]);
                        O_BoxInt[BoxInt1] = {j,i};
                        count++;
                    }


                }
                else if (TCODConsole::root -> getChar(j, i) == 'X'){
                    TCODConsole::root->setCharBackground(j,i,colourVec[2]);
                    if(count1%2==0){
                        Mark<char>MarkChar1(j,i,'X');
                        //TCODConsole::root->setChar(j,i,'X');
                        //TCODConsole::root->setCharBackground(j,i,colourVec[2]);
                        X_MarkChar[{j,i}] = MarkChar1;
                        count1++;
                    } else{
                        Mark<int>MarkInt1(j,i,'X');
                        //TCODConsole::root->setChar(j,i,'X');
                        //TCODConsole::root->setCharBackground(j,i,colourVec[2]);
                        X_MarkInt[{j,i}] = MarkInt1;
                        count1++;
                    }
                }
            }
        }
        TCODConsole::root->flush();
    }
    bool ifWin(map<vector<int>,char>& X_mark){
        decltype(X_mark.size()) winCnt = 0;
        for (auto cross : X_mark){
            if (cross.second == 'O'){
                winCnt++;
            }
        }
        if (winCnt == X_mark.size()) {
            return true;
        }
        else{
            return false;
        }
    }


private:
    int count=0;
    int count1=0;
    unsigned length;
    unsigned width;
    T **val;

};

#endif //PROJECT_BOARD_H
