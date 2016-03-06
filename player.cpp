#include "player.h"

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
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

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
    board.pickMove(me, opponent, true);
    if (board.bestMove != NULL)
    {
        Move * toReturn = new Move(board.bestMove->x, board.bestMove->y);
        board.doMove(toReturn, me);
        return toReturn;
    }
    return NULL;

    /*
    vector<Move *> myMoves = board.possibleMoves(me);
    if (myMoves.size() >= 1)
    {
        Move * toReturn = new Move(myMoves[0]->x, myMoves[0]->y);
        board.doMove(toReturn, me);
        return toReturn; //hi
    }
    */
    //return NULL;
}
