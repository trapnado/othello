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
      
public:
    Board();
    ~Board();
    Board *copy();
        
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();

    void setBoard(char data[]);
};

#endif
