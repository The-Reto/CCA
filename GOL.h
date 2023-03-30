#ifndef GOL_H
#define GOL_H

#include <iostream>
#include <bitset>
#include <climits>
#include "BitBoard.h"

class GOL {
    protected:
    int sizex, sizey;
    BitBoard  board,  b_board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    public:
    GOL(int sx, int sy, unsigned int seed);
    
    GOL(unsigned int seed);
    
    GOL();
    
    void set_rules(bool survive_[9], bool create_[9]);
    
    void step();
    
    void steps(int steps);
    
    void print();
    
    BitBoard get_board();
};
#endif
