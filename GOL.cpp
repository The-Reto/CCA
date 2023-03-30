#ifndef GOL_CPP
#define GOL_CPP

#include <iostream>
#include <bitset>
#include <climits>
#include "BitBoard.cpp"

template <int sizex, int sizey> class GOL {
    protected:
    BitBoard  board,  b_board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    public:
    GOL(unsigned int seed) {
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        board = BitBoard(sizex, sizey);
        b_board = BitBoard(sizex, sizey);
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            board.set(5,i+3, s[i]);
        }
    }
    
    void set_rules(bool survive_[9], bool create_[9]){
        for (int i = 0; i < 9; i++) {
            survive[i] = survive_[i];
            create[i] = create_[i];
        }
    }
    
    void step() {
        int neighbours = 0;
        for (int i = 0; i < sizex*sizey; i++) {
            neighbours = board.count_neighbours(i);
            b_board.set(i, board.get(i) * survive[neighbours] + (1 -  board.get(i)) * create[neighbours] );
        }
        board = b_board;
    }
    
    void steps(int steps){
        for (int i = 0; i < steps; i++) { step(); }
    }
    
    void print() {
        board.visualize();
    }
    
    BitBoard get_board() {
        return board;
    }
};
#endif
