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
    const TCODColor box{144, 238, 144};
    const TCODColor hole{255, 255, 255};
    const vector<TCODColor> colourVec = {player, wall, box, hole};
    vector<int> Player;
    map<Box <char>,vector <int> >O_BoxChar;
    map<Box <int>,vector <int> >O_BoxInt;
    map<vector<int>,Mark <char> >X_MarkChar;
    map<vector<int>,Mark <int> >X_MarkInt;
    TestBoard.GameMap(TestBoard, colourVec, Player, X_MarkChar,X_MarkInt, O_BoxChar,O_BoxInt);
    while (/*!TestBoard.ifWin(X_Mark) &&*/ EndOfGame(0)) {
        /*updateWinPositions(X_MarkChar,X_MarkInt,O_BoxChar,O_BoxInt, colourVec);*/
        chkKeyPressAndMovePlayer(Player, colourVec,X_MarkChar,X_MarkInt, O_BoxChar,O_BoxInt);
    }
    /*while(1) {
    }*/
}