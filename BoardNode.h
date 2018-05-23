//
// Created by EricLaptop on 5/19/2018.
//

#ifndef ISOC_BOARDNODE_H
#define ISOC_BOARDNODE_H




#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

class BoardNode{
private:


    char oRowPos;
    char oColPos;


public:
    int xMoves;
    int oMoves;
    int score;



    BoardNode();
    BoardNode(char firstPlayer);
    //BoardNode(const BoardNode &parent);


    ~BoardNode();
    bitset<8> board[8];

    void printBoard();


    bool set(char row, char col);

    bool moveX(char row, char col);

    bool xLegalMove(char row, char col);

    bool look(char row, char col)const;

    bool oLegalMove(char row, char col);

    bool moveO(char row, char col);

    char xPossibleMoves();

    char oPossibleMoves();

    vector<tuple<char,char>> *xListPossibleMoves();

    vector<tuple<char, char>> *oListPossibleMoves();

    vector<BoardNode> * xCreateChildren();

    char xRowPos;
    char xColPos;

    BoardNode(BoardNode *pNode);

    void updateScore();

    static bool sortByScore(const BoardNode &lhs, const BoardNode &rhs);

    static bool sortByScoreReverse(const BoardNode &lhs, const BoardNode &rhs);

    vector<BoardNode> *oCreateChildren();

    vector<BoardNode> * children;
};

#endif //ISOC_BOARDNODE_H

