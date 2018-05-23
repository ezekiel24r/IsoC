
using namespace std;
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include "BoardNode.h"
#include "AlphaBeta.h"

tuple<char, char> parseInput(string in);

int main(){
    /*
    cout << "hello world\n";
    bitset<8> board[8];
    board[0][0] = 1;
    board[1][1] = 1;
    board[2][2] = 1;
    cout << board[0][0] << " " << board[0][1] << endl;
    cout << board[2] << endl;
     */


    /*BoardNode *b = nullptr;
    b = new BoardNode('X');

    b->printBoard();

    cout << b->moveX(1,1);

    b->printBoard();

    cout << b->moveX(0,0);
    b->printBoard();

    char x = b->xPossibleMoves();
    cout << (int)x << endl;

    b->printBoard();

    auto *v = new vector<BoardNode>;

    v = b->xCreateChildren();

    b->printBoard();

    sort(v->begin(),v->end(),BoardNode::sortByScore);

    tuple<char,char> move = AlphaBeta::getBestMove(b);

    b->moveX(get<0>(move), get<1>(move));

    b->printBoard();

    cout << "Blaaaah" << endl;

    delete b;*/

    cout << "Welcome!" << endl;

    cout << "Who is playing first?"
           << "\n Enter 1 to go first, or 2 to go second" << endl;
    int choice;
    cin >> choice;
    cin.ignore();
    string playerMove;

    BoardNode *b = nullptr;
    tuple<char, char> move;


    switch(choice){

        case 1:

                cout << "Player goes first!" << endl;
                b = new BoardNode('O');
                b->printBoard();
            while(true) {

                cout << "Enter player move: " << endl;
                getline(cin, playerMove);
                move = parseInput(playerMove);
                if(b->oLegalMove(get<0>(move),get<1>(move))){
                    b->moveO(get<0>(move), get<1>(move));
                }
                else{
                    cout<< "Invalid move!" << endl;
                    continue;
                }

                b->printBoard();

                move = AlphaBeta::getBestMove(b);
                b->moveX(get<0>(move), get<1>(move));
                b->printBoard();

            }

            break;

        case 2:


            cout << "Computer goes first!" << endl;
            b = new BoardNode('X');
            b->printBoard();
            move = AlphaBeta::getBestMove(b);
            b->moveX(get<0>(move), get<1>(move));
            b->printBoard();

            break;
        default:

            break;
    }


    return 0;
}

tuple<char, char> parseInput(string in){
    tuple<char, char> result;
    if(in.length()==2){
        get<0>(result) = in.at(0)-65;
        get<1>(result) = in.at(1)-49;
    }
    else{
        get<0>(result) = 0;
        get<1>(result) = 0;
    }
    return result;

};

