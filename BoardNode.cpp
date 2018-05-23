//
// Created by EricLaptop on 5/19/2018.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <tuple>

#include "BoardNode.h"

using namespace std;

BoardNode::BoardNode(){
    for(char i=0; i<8; i++){
        board[i].reset();
    }


    xRowPos = 0;
    xColPos = 0;
    oRowPos = 7;
    oColPos = 7;
    set(0,0);
    set(7,7);
    updateScore();


    children = new vector<BoardNode>();

}

BoardNode::BoardNode(char firstPlayer = 'X'){
    for(char i=0; i<8; i++){
        board[i].reset();
    }

    if(firstPlayer == 'X'){
        xRowPos = 0;
        xColPos = 0;
        oRowPos = 7;
        oColPos = 7;
    }else{
        xRowPos = 7;
        xColPos = 7;
        oRowPos = 0;
        oColPos = 0;
    }
    set(0,0);
    set(7,7);
    updateScore();


    children = new vector<BoardNode>();

}


/*BoardNode::BoardNode(const BoardNode &parent){
    for(char i=0; i<8; i++){
        board[i].reset();
    }


    xRowPos = parent.xRowPos;
    xColPos = parent.xColPos;
    oRowPos = parent.oRowPos;
    oColPos = parent.oColPos;
    updateScore();

    for(char i=0; i<8; i++){
        for(char j=0; j<8; j++){
            if(parent.look(i,j)){
                set(i,j);
            }
        }
    }



    children = new vector<BoardNode>();

}*/


BoardNode::BoardNode(BoardNode *parent) {
    for(char i=0; i<8; i++){
        board[i].reset();
    }


    xRowPos = parent->xRowPos;
    xColPos = parent->xColPos;
    oRowPos = parent->oRowPos;
    oColPos = parent->oColPos;
    updateScore();

    for(char i=0; i<8; i++){
        for(char j=0; j<8; j++){
            if(parent->look(i,j)){
                set(i,j);
            }
        }
    }



    children = new vector<BoardNode>();
}


BoardNode::~BoardNode(){
    children = NULL;
    delete [] children;
}

bool BoardNode::look(char row, char col)const {
    return board[row][col];
}
bool BoardNode::set(char row, char col){
    board[row][col] = true;
}

void BoardNode::updateScore(){
    xMoves = xPossibleMoves();
    oMoves = oPossibleMoves();
    score = xMoves - oMoves;
}

bool BoardNode::moveX(char row, char col){
    if(xLegalMove(row, col)){
        xRowPos = row;
        xColPos = col;
        set(row, col);
        updateScore();
        return true;
    }
    return false;

}

bool BoardNode::moveO(char row, char col){
    if(oLegalMove(row, col)){
        oRowPos = row;
        oColPos = col;
        set(row, col);
        updateScore();
        return true;
    }
    return false;

}

bool BoardNode::xLegalMove(char row, char col){
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    if(look(row, col) != 0){
        return false;
    }
    //right move
    if(row == xRowPos && col > xColPos){
        char colPtr = col;
        while(colPtr > xColPos+1){
            colPtr--;
            if(look(xRowPos, colPtr) == 1){
                return false;
            }
        }
        return true;
    }
    //left move
    if(row == xRowPos && col < xColPos){
        char colPtr = col;
        while(colPtr < xColPos-1){
            colPtr++;
            if(look(xRowPos, colPtr) == 1){
                return false;
            }
        }
        return true;
    }
    //up move
    if(row < xRowPos && col == xColPos){
        char rowPtr = row;
        while(rowPtr < xRowPos-1){
            rowPtr++;
            if(look(rowPtr, xColPos) == 1){
                return false;
            }
        }
        return true;
    }
    //down move
    if(row > xRowPos && col == xColPos){
        char rowPtr = row;
        while(rowPtr > xRowPos+1){
            rowPtr--;
            if(look(rowPtr, xColPos) == 1){
                return false;
            }
        }
        return true;
    }
    //up right move
    if(row < xRowPos && col > xColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr < xRowPos-1 && colPtr > xColPos+1){
            rowPtr++;
            colPtr--;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr++;
        colPtr--;
        return xRowPos == rowPtr && xColPos == colPtr;
    }
    //down right move
    if(row > xRowPos && col > xColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr > xRowPos+1 && colPtr > xColPos+1){
            rowPtr--;
            colPtr--;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr--;
        colPtr--;
        return xRowPos == rowPtr && xColPos == colPtr;
    }
    //down left move
    if(row > xRowPos && col < xColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr > xRowPos+1 && colPtr < xColPos-1){
            rowPtr--;
            colPtr++;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr--;
        colPtr++;
        return xRowPos == rowPtr && xColPos == colPtr;
    }
    //up left move
    if(row < xRowPos && col < xColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr < xRowPos-1 && colPtr < xColPos-1){
            rowPtr++;
            colPtr++;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr++;
        colPtr++;
        return xRowPos == rowPtr && xColPos == colPtr;
    }
    return false;
}

bool BoardNode::oLegalMove(char row, char col){
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    if(look(row, col) != 0){
        return false;
    }
    //right move
    if(row == oRowPos && col > oColPos){
        char colPtr = col;
        while(colPtr > oColPos+1){
            colPtr--;
            if(look(oRowPos, colPtr) == 1){
                return false;
            }
        }
        return true;
    }
    //left move
    if(row == oRowPos && col < oColPos){
        char colPtr = col;
        while(colPtr < oColPos-1){
            colPtr++;
            if(look(oRowPos, colPtr) == 1){
                return false;
            }
        }
        return true;
    }
    //up move
    if(row < oRowPos && col == oColPos){
        char rowPtr = row;
        while(rowPtr < oRowPos-1){
            rowPtr++;
            if(look(rowPtr, oColPos) == 1){
                return false;
            }
        }
        return true;
    }
    //down move
    if(row > oRowPos && col == oColPos){
        char rowPtr = row;
        while(rowPtr > oRowPos+1){
            rowPtr--;
            if(look(rowPtr, oColPos) == 1){
                return false;
            }
        }
        return true;
    }
    //up right move
    if(row < oRowPos && col > oColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr < oRowPos-1 && colPtr > oColPos+1){
            rowPtr++;
            colPtr--;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr++;
        colPtr--;
        return oRowPos == rowPtr && oColPos == colPtr;
    }
    //down right move
    if(row > oRowPos && col > oColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr > oRowPos+1 && colPtr > oColPos+1){
            rowPtr--;
            colPtr--;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr--;
        colPtr--;
        return oRowPos == rowPtr && oColPos == colPtr;
    }
    //down left move
    if(row > oRowPos && col < oColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr > oRowPos+1 && colPtr < oColPos-1){
            rowPtr--;
            colPtr++;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr--;
        colPtr++;
        return oRowPos == rowPtr && oColPos == colPtr;
    }
    //up left move
    if(row < oRowPos && col < oColPos){
        char rowPtr = row;
        char colPtr = col;
        while(rowPtr < oRowPos-1 && colPtr < oColPos-1){
            rowPtr++;
            colPtr++;
            if(look(rowPtr, colPtr) == 1){
                return false;
            }
        }
        rowPtr++;
        colPtr++;
        return oRowPos == rowPtr && oColPos == colPtr;
    }
    return false;
}

char BoardNode::xPossibleMoves(){
    char sum = 0;
    for(char i=0; i<8; i++){
        for(char j=0; j<8; j++){
            if(xLegalMove(i,j)){
                sum++;
            }
        }
    }

    return sum;
}

char BoardNode::oPossibleMoves(){
    char sum = 0;
    for(char i=0; i<8; i++){
        for(char j=0; j<8; j++){
            if(oLegalMove(i,j)){
                sum++;
            }
        }
    }
    return sum;
}

vector<tuple<char,char>> * BoardNode::xListPossibleMoves(){
    auto * moves = new vector<tuple<char,char>> ;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(xLegalMove(i,j)){
                tuple<char,char> p;
                get<0>(p) = i;
                get<1>(p) = j;
                moves->push_back(p);
            }
        }
    }
    return moves;
}

vector<tuple<char,char>> * BoardNode::oListPossibleMoves(){
    auto * moves = new vector<tuple<char,char>> ;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(oLegalMove(i,j)){
                tuple<char,char> p;
                get<0>(p) = i;
                get<1>(p) = j;
                moves->push_back(p);
            }
        }
    }
    return moves;
}

vector<BoardNode> * BoardNode::xCreateChildren(){
    auto * moves = xListPossibleMoves();
    auto * results = new vector<BoardNode>;
    BoardNode * temp = nullptr;
    char row, col;
    for(int i=0; i<moves->size(); i++){
        tuple<char,char> p;
        p = moves->at(i);
        row = get<0>(p);
        col = get<1>(p);


        temp = new BoardNode(this);
        temp->moveX(row, col);
        //this.children.add(temp);
        results->push_back(temp);
    }
    //delete [] moves;
    return results;
}

vector<BoardNode> * BoardNode::oCreateChildren(){
    auto * moves = oListPossibleMoves();
    auto * results = new vector<BoardNode>;
    BoardNode * temp = nullptr;
    char row, col;
    for(int i=0; i<moves->size(); i++){
        tuple<char,char> p;
        p = moves->at(i);
        row = get<0>(p);
        col = get<1>(p);

        temp = new BoardNode(this);
        temp->moveO(row, col);
        //this.children.add(temp);
        results->push_back(temp);
    }
    //delete moves;
    return results;
}

void BoardNode::printBoard(){
    cout << "\n\n  ";
    for(int i=0; i<8; i++){
        cout << i+1 << " ";
    }
    cout << "  Computer vs. Opponent\n";
    for(int i=0; i<8; i++){
        cout << (char)(i+65) << " ";
        for(int j=0; j<8; j++){
            if(xRowPos == i && xColPos == j){
                cout << "X ";
            } else if(oRowPos == i && oColPos == j){
                cout << "O ";
            } else if(look(i,j) == 0){
                cout << "- ";
            } else{
                cout << "# ";
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

bool BoardNode::sortByScore(const BoardNode &lhs, const BoardNode &rhs){
    return lhs.score < rhs.score;
}

bool BoardNode::sortByScoreReverse(const BoardNode &lhs, const BoardNode &rhs){
    return lhs.score < rhs.score;
}
