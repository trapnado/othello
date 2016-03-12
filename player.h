#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
	Side me, opponent;
	Board board; //More pointers more problems. 
	int maxDepthLimit; //Maximum Depth player will consider.
	int depthLimit; // How far deep the player is currently going to search.
	int moveNumber;
	// HOw much time we had at start of last move.
	int prevMoveStartTime;
	int myMoveTimes[64];

    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    int ab(Board * tBoard, Side mySide, Side oppSide, int alpha, int beta);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
