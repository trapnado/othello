#ifndef __COMMON_H__
#define __COMMON_H__

#include <vector>
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
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

#endif
