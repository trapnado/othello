/* LAST FULL UPDATE 3/6/2016 1:19
 * Code outline- a quick reference for files/classes/functions/object types.
 * I am doing this at the start of the project as a way to get my bearings;
 * I'm not sure it will be worth it to keep it updated as time goes on.
 * Is a cpp file so my text editor will color it like C++ code. NOT meant to 
 * be compiled.
 */

==================* common.h *=====================
/* Attempted synopsis of enum's: an enum instance takes 
 * one of the possible enum types, and never changes. Each type corresponds
 * to an integer value-WHITE is probably 0 and BLACK is probably 1. 
 * Syntax example: Side mySide = BLACK; (later) 
 * If(mySide == BLACK) {}<- will execute.
 */
enum Side { 
    WHITE, BLACK
};

class Move {
public:
    int x, y;
    Move(int x, int y) {} //Is defined here, actually. Does what you'd expect.
    ~Move() {}
    int getX() { return x; }
    int getY() { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

==================* board.h *=====================
// Everything here is implemented in Board. Nothing else is.
class Board {
private:
	// These 64 bitsets define the 8x8 board.
    /* bitsets are literally a block of single bits in memory, each of
     * which can be 0 or 1. On creation they are all 0's. 
     * I'm not sure we ever need to mess with these because of board's
     * functions. */
    bitset<64> black;
    bitset<64> taken;   
    /* Well...maybe. I can see wanting to store a bit more info about
     * the context of some of the pieces, specifically if something is
     * interior or not, so that doesn't have to be recomputed. */  
       
    bool occupied(int x, int y);
    bool get(Side side, int x, int y); //True if 'side' has piece there.
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
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
	// Board initializes to standard othello opening board.
    Board();
    ~Board();
    // copy() calls new.
    Board *copy();
        
    bool isDone(); // Is the game over?
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    vector<Move *> possibleMoves(Side side);
    // doMove will flip the opponent's pieces appropriately when called. 
    void doMove(Move *m, Side side); 
    int count(Side side);
    int countBlack();
    int countWhite();
    /* Sets the board state given an 8x8 char array where 'w' indicates a white
    * piece and 'b' indicates a black piece. Mainly for testing purposes. */
    void setBoard(char data[]);
};

==================* player.h *=====================
// Player is NOT implemented.
class Player {
public:
	Side me, opponent;
	Board board; //More pointers more problems. 
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};