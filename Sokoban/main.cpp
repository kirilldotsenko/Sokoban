#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <libtcod.hpp>
#include "GameFunctions.h"
#include "cmake-build-debug/Board.h"
#include <boost/any.hpp>
using namespace std;

int main() {
    ifstream in("map.txt");
    TwoD<char> TestBoard;
    in >> TestBoard;
    TCODConsole::initRoot(TestBoard.GetDmX(), TestBoard.GetDmY(), "SOKOBAN");
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
    map<Box <char>,vector <int> >O_BoxChar;
    map<Box <int>,vector <int> >O_BoxInt;
    map<CommonBox,vector<int>>O_Box;
    map<Mark <char>,vector <int> >X_MarkChar;
    map<Mark <int>,vector <int> >X_MarkInt;
    map<CommonMark,vector<int>>X_Mark;
    TestBoard.GameMap(TestBoard, colourVec, Player, X_MarkChar,X_MarkInt, O_BoxChar,O_BoxInt,TypeBox,X_Mark,O_Box);
    int counter=0;
    while (TestBoard.ifWin(X_MarkChar,X_MarkInt,X_Mark,counter) && EndOfGame(0)) {
        counter=updateWinPositions(X_MarkChar,X_MarkInt,O_BoxChar,O_BoxInt,O_Box,X_Mark, colourVec);
        chkKeyPressAndMovePlayer(TestBoard,Player, colourVec, O_BoxChar,O_BoxInt,O_Box);
    }
    /*while(1) {
    }*/
}