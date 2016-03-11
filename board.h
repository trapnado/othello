#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;

class Board {
   
private:
    // These 64 bitsets define the 8x8 board.
    /* bitsets are literally a block of single bits in memory, each of
     * which can be 0 or 1. On creation they are all 0's. 
     * I'm not sure we ever need to mess with these because board's
     * functions seem to have that covered. */
    bitset<64> black;
    bitset<64> taken;    
    /* Well...maybe. I can see wanting to store a bit more info about
     * the context of some of the pieces, specifically if something is
     * interior or not, so that doesn't have to be recomputed. */ 

       
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
    int weightedCount(Side me);
    void bitsetBoard(bitset<64> tkn, bitset<64> blck);
      
public:
    /*
    // All 64 possible moves. Declared static because its for reference; there
    // is no need to have more than one copy of it.
    // Remember: row first, then column.
    */
    static Move * const allMoves [8][8];
    int bestScore;
    Move * bestMove;
    static int const baseWeight [8][8];
    /* The depth of this board in the alpha-beta pruning.
     * Will also be useful if we do any transposition.
     * A DEPTH OF 0 in the search means that this board is the root.
     * In a transposition table, depth is the number of levels after
     * this board that were evaluated in determining its statistics.
     */
    int depth; 
    Side side; // Which side the "bestScore" and "BestMove" apply to.


    /*
    vector<Move *> legalBlackMoves;
    vector<Move *> legalWhiteMoves; */

    Board();
    ~Board();
    Board *copy();
    // An adjusted copying function for use in ab
    Board *abNextBoard(Side newSide);
        
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    vector<Move *> possibleMoves(Side side);
    void doMove(Move *m, Side side);

    void pickMove(Side me, Side opponent, bool testingminimax);
    int scoreBoard(Side me, Side opponent, bool testingminimax);

    int count(Side side);
    int countBlack();
    int countWhite();


    void setBoard(char data[]);
};

#endif
