#include "player.h"
#define TIMING_SIZE 10
#define EXPECTED_NUM_MOVES 36

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false; 
    me = side;
    if(me == BLACK)
    {
        opponent = WHITE;
    }
    else
    {
        opponent = BLACK;
    }
    board = Board(); 
    board.side = side;
    moveNumber = 0;
    // HOw much time we had at start of last move.
    prevMoveStartTime = -1; //We haven't had a move yet.
    //the myMoveTimes also doesn't need anything ihnteresting.
    depthLimit = 7;
    maxDepthLimit = 7;
    //Just an initialization
    for (int i = 0; i < 64; i++)
    {
        myMoveTimes[i] = 0;
    }
    
    

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

// THis currently sets maxDepthLimit, the maximum that it is willing to 
// search in this stage of the game; it will choose 
// if stoneCount > timing[i], stoneCount < timing[i+1], depth = i
// depth to go to:           0, 1, 2, 3, 4, 5, 6, 7, 8,  9,  10
int timing[TIMING_SIZE+1] = {0, 0, 0, 0, 0, 0, 0, 0, 24, 45, 100};
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    board.doMove(opponentsMove, opponent);
    myMoveTimes[moveNumber] = prevMoveStartTime - msLeft;
    
    prevMoveStartTime = msLeft;

	int stones = board.countBlack() + board.countWhite();
    if (moveNumber > 0)
    {
        if ((EXPECTED_NUM_MOVES - moveNumber) * myMoveTimes[moveNumber] 
             > msLeft && depthLimit > 0)
        {
            depthLimit--;
        }
        else if ((EXPECTED_NUM_MOVES - moveNumber) * myMoveTimes[moveNumber] 
            - stones
            < msLeft)
        {
            depthLimit++;
        }
    }
    moveNumber++;

    
    int stones = board.countBlack() + board.countWhite();
    for (int i = 0; i < TIMING_SIZE; i++)
    {
        if (stones>timing[i] && stones < timing[i+1])
        {
            maxDepthLimit = i;
        }
    }
    
    board.bestScore = -10000;
    board.bestMove = NULL;
    int alpha = -10000, beta = 10000;
    // CHoose the best move; store it to my board.
    ab(&board, me, opponent, alpha, beta);
    
    board.doMove(board.bestMove, me);
    Move * toReturn = NULL;
    if (board.bestMove != NULL)
    {
        toReturn = new Move(board.bestMove->x, board.bestMove->y);
    }

    std::cerr << "Approximate minutes left: " << (double)msLeft/60.0/1000.0
     << std::endl;
    return toReturn;

}

// The tBoard carries your side-so only oppSide needed--this is just for 
// convenience
int Player::ab(Board * tBoard, Side mySide, Side oppSide, int alpha, int beta)
{
    if (tBoard->depth == depthLimit)
        return tBoard->scoreBoard(mySide, oppSide, false);
    vector<Move *> moves = tBoard->possibleMoves(mySide);
    int score;
    if (moves.size() == 0)
    {
        if (!tBoard->hasMoves(opponent))
        {
            if (tBoard->depth <= 1)
            {
                board.thisIsLastMove = true;
            }
            // This is a game end state. Weight it accordingly.
            return 100000 * tBoard->scoreBoard(mySide, oppSide, true);
        }
        else
        {
            Board * temp_board = tBoard->abNextBoard(oppSide);
            return -ab(temp_board, oppSide, mySide, -beta, -alpha);
        }
    }
    tBoard->bestMove = moves[0];
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        Board * temp_board = tBoard->abNextBoard(oppSide);
        temp_board->doMove(moves[i], mySide);
        score = -ab(temp_board, oppSide, mySide, -beta, -alpha);
        delete temp_board; // Consider doing storing to transposition tables!
        if (score > alpha)
        {
            alpha = score;
            tBoard->bestMove = moves[i];
            tBoard->bestScore = alpha;
        }
        if (score >= beta)
            break;
    }

    return alpha;
}
