#include "board.h"




Move * const Board::allMoves [8][8] = {
    {new Move(0,0), new Move(0,1), new Move(0,2), new Move(0,3), 
     new Move(0,4), new Move(0,5), new Move(0,6), new Move(0,7)},
    {new Move(1,0), new Move(1,1), new Move(1,2), new Move(1,3), 
     new Move(1,4), new Move(1,5), new Move(1,6), new Move(1,7)},
    {new Move(2,0), new Move(2,1), new Move(2,2), new Move(2,3), 
     new Move(2,4), new Move(2,5), new Move(2,6), new Move(2,7)},
    {new Move(3,0), new Move(3,1), new Move(3,2), new Move(3,3), 
     new Move(3,4), new Move(3,5), new Move(3,6), new Move(3,7)},
    {new Move(4,0), new Move(4,1), new Move(4,2), new Move(4,3), 
     new Move(4,4), new Move(4,5), new Move(4,6), new Move(4,7)},
    {new Move(5,0), new Move(5,1), new Move(5,2), new Move(5,3), 
     new Move(5,4), new Move(5,5), new Move(5,6), new Move(5,7)},
    {new Move(6,0), new Move(6,1), new Move(6,2), new Move(6,3), 
     new Move(6,4), new Move(6,5), new Move(6,6), new Move(6,7)},
    {new Move(7,0), new Move(7,1), new Move(7,2), new Move(7,3), 
     new Move(7,4), new Move(7,5), new Move(7,6), new Move(7,7)}
};

/* cor|ncr|edg ...etc.
 * ncr|dcr|nor
 * edg|nor|nor
 * ...
 * etc.
 * cor = corner, ncr = edge next to corner,
 * dcr = diagonal next to corner
 * nor = normal
 */
int scalar = 4;
int mobility = 3, frontier = 1;
int cor = 10 * scalar, ncr = 0 * scalar, dcr = -5 * scalar, nor = 2 * scalar, edg = 4 *scalar; 

int Board::baseWeight [8][8] = {
{cor, ncr, edg, edg, edg, edg, ncr, cor},
{ncr, dcr, nor, nor, nor, nor, dcr, ncr},
{edg, nor, nor, nor, nor, nor, nor, edg},
{edg, nor, nor, nor, nor, nor, nor, edg},
{edg, nor, nor, nor, nor, nor, nor, edg},
{edg, nor, nor, nor, nor, nor, nor, edg},
{ncr, dcr, nor, nor, nor, nor, dcr, ncr},
{cor, ncr, edg, edg, edg, edg, ncr, cor}
};
/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
    depth = 0;
    side = BLACK; 
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    newBoard->side = side;
    newBoard->depth = depth;
    return newBoard;
}

/* Increases the depth by 1 and switches sides to the passed side. */
Board *Board::abNextBoard(Side newSide) {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    newBoard->side = newSide;
    newBoard->depth = depth + 1;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}

 
/*
 * Returns true if the game is finished; false otherwise. The game is finished 
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            //Move move(i, j);
            if (checkMove(allMoves[i][j], side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == NULL) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Returns a vector of pointers to all possible Moves.
 */
vector<Move *> Board::possibleMoves(Side side){
    vector<Move *> myMoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (checkMove(allMoves[i][j], side)) 
                myMoves.push_back(allMoves[i][j]);
        }
    }
    return myMoves;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A NULL move means pass.
    if (m == NULL) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;
    if (m == allMoves[0][0])
    {
		baseWeight[0][1] = edg;
		baseWeight[1][0] = edg;
		baseWeight[1][1] = nor;
	}
	else if (m == allMoves[0][7])
    {
		baseWeight[0][6] = edg;
		baseWeight[1][7] = edg;
		baseWeight[1][6] = nor;
	}
	else if (m == allMoves[7][0])
    {
		baseWeight[6][0] = edg;
		baseWeight[7][1] = edg;
		baseWeight[6][1] = nor;
	}
	else if (m == allMoves[7][7])
    {
		baseWeight[7][6] = edg;
		baseWeight[6][7] = edg;
		baseWeight[6][6] = nor;
	}

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/* 
 * Picks the best move for the given side on this board.
 * Stores the move's score to bestScore and the move * to bestMove.
 */
void Board::pickMove(Side me, Side opponent, bool testingminimax)
{
    bestScore = -255;
    bestMove = NULL;
    int score;
    //bitset<64> blck = black;
    //bitset<64> tkn = taken;
    Board *test;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (checkMove(allMoves[i][j], me)) 
            {
                test = copy();
                test->doMove(allMoves[i][j], me);
                score = test->scoreBoard(me, opponent, testingminimax);
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = allMoves[i][j];
                }
                delete test;
                //black = blck;
                //taken = tkn;
            }
        }
    }
}

// Returns the score of current board for a particular side.
int Board::scoreBoard(Side me, Side opponent, bool testingminimax)
{
    if(testingminimax)
    {
        return count(me)-count(opponent);
    }
    else
    {
        return (weightedCount(me) - weightedCount(opponent));
    }
}

int Board::weightedCount(Side me)
{
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (get(me, i, j))
            {
                score+= baseWeight[i][j];
            }
            else if (!occupied(i, j))
            {
				for (int l = -1; l < 2; l++)
				{
					for (int k = -1; k < 2; k++)
					{
						if (onBoard(i + l, j + k))
						{
						if (get(me, i + l, j + k))
						{
							score -= frontier;
						}
						}
					}
				}
			}
            
        }
    }
    score += mobility * possibleMoves(me).size();
    return score;    
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}

/*
 * Sets the board state given a 64-long bitset for taken
 * and a 64 long bitset for black. Mainly for testing purposes.
 */
void Board::bitsetBoard(bitset<64> tkn, bitset<64> blck) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (tkn[i]) {
            taken.set(i);
            if (blck[i])
            {
                black.set(i);
            }  
        }
    }
}
