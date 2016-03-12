#include "player.h"
#define TIMING_SIZE 10

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
    board.playerSide = side;
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

	board.bestScore = -10000;
	board.bestMove = NULL;
    //depthLimit = 7;
    int stones = board.countBlack() + board.countWhite();
    for (int i = 0; i < TIMING_SIZE; i++)
    {
        if (stones>timing[i] && stones < timing[i+1])
        {
            depthLimit = i;
        }
    }
    int alpha = -10000, beta = 10000;
    // CHoose the best move; store it to my board.
    ab(&board, me, opponent, alpha, beta);
    
    board.doMove(board.bestMove, me);
    Move * toReturn = NULL;
    if (board.bestMove != NULL)
    {
        toReturn = new Move(board.bestMove->x, board.bestMove->y);
    }
/*
    if (board.thisIsLastMove)
    {
        std::cerr << "End in sight. My (with heuristic) score: "
         << board.scoreBoard(me, opponent, false) << std::endl;
        std::cerr << "I had "<< msLeft << " ms left before this last move." 
         << std::endl;
    }
    else if (board.bestScore > 1000)
    {
        std::cerr << "Game end in sight."
         << board.scoreBoard(me, opponent, false) << std::endl;
        std::cerr << "I had "<< msLeft << " ms left before this move." 
         << std::endl;
    }*/
    std::cerr << "Approximate minutes left: " << msLeft/1000/60 << std::endl;
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
