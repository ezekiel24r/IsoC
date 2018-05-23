//
// Created by EricLaptop on 5/22/2018.
//
#include "AlphaBeta.h"
#include <algorithm>

tuple<char,char> AlphaBeta::getBestMove(BoardNode *node){
        auto * temp = new BoardNode(node);
        //auto * best = new BoardNode(node);
        temp->printBoard();
        //best->printBoard();
        //auto * v = temp->xCreateChildren();

        time_t initTime, currentTime;
        initTime = time(NULL);

        temp->children = new vector<BoardNode>;

        int initialDepth = 2;
        while(initialDepth < 5){
            //temp->children = new vector<BoardNode>;
            alphaBeta(temp,initialDepth, INT_MIN, INT_MAX, true, initTime);
            initialDepth++;
            cout << "depth = " << initialDepth << endl;

        }
        sort(temp->children->begin(),temp->children->end(), BoardNode::sortByScore);
        reverse(temp->children->begin(),temp->children->end());

        //sort(v->begin(),v->end(),BoardNode::sortByScore);
        char row, col;
        row = temp->children->at(0).xRowPos;
        col = temp->children->at(0).xColPos;

        tuple<char,char> result;

        get<0>(result) = row;
        get<1>(result) = col;

        return result;

}

int AlphaBeta::alphaBeta(BoardNode * node, int depth, int alpha, int beta, bool maxPlayer, long &startTime) {
        auto *moves = new vector<BoardNode>;
        int val;

        if (depth == 0)
                return node->score;
        if (node->xMoves == 0) {
            node->score = -999999999;
                return -999999999;

        }
        if (node->oMoves == 0) {
            node->score = 999999999;
                return 999999999;
        }


        if (maxPlayer) {
                val = INT_MIN;
                node->children = node->xCreateChildren();
                //moves = node->xCreateChildren();
                //sort(moves->fr(), moves->back(), BoardNode::sortByScore);

                for (int i = 0; i < node->children->size(); i++) {
                        val = max(val, alphaBeta(&node->children->at(i), depth - 1, alpha, beta, false, startTime));
                        //node->score = val;
                        alpha = max(alpha, val);
                        if (beta <= alpha) {
                                break;
                        }
                }
                return val;
        } else {
                val = INT_MAX;
                node->children = node->oCreateChildren();

                //moves = node->oCreateChildren();
                //sort(moves->front(), moves->back(), BoardNode::sortByScoreReverse);

                for (int i = 0; i < node->children->size(); i++) {
                        val = min(val, alphaBeta(&node->children->at(i), depth - 1, alpha, beta, true, startTime));
                        node->score = val;
                        alpha = min(alpha, val);
                        if (beta <= alpha) {
                                break;
                        }
                }
                return val;
        }
}