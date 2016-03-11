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
    board.side = side;
    //std::cerr << "Successful Initialization! " << std::endl;
    //Depth is automatically set to 0.
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

	board.bestScore = -10000;
	board.bestMove = NULL;
    depthLimit = 4;
    int alpha = -10000, beta = 10000;
    // CHoose the best move; store it to my board.
    ab(&board, me, opponent, alpha, beta);
    
    board.doMove(board.bestMove, me);
    Move * toReturn = NULL;
    if (board.bestMove != NULL)
    {
        toReturn = new Move(board.bestMove->x, board.bestMove->y);
    }
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
            // This is a game end state. Weight it accordingly.
            return 1000 * tBoard->scoreBoard(mySide, oppSide, true);
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