//
// Created by EricLaptop on 5/22/2018.
//

#ifndef ISOC_ALPHABETA_H
#define ISOC_ALPHABETA_H




#include <ctime>
#include <algorithm>
#include <tuple>
#include <climits>
#include "BoardNode.h"

class AlphaBeta{
public:
    static tuple<char,char> getBestMove(BoardNode *node);

    static int alphaBeta(BoardNode *node, int depth, int alpha, int beta, bool maxPlayer, long &startTime);
};

#endif //ISOC_ALPHABETA_H