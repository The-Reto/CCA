#ifndef GOL_CPP
#define GOL_CPP

#include <iostream>
#include <bitset>
#include <climits>
#include "BitBoard.cpp"

template <int sizex, int sizey> class GOL {
    protected:
    BitBoard<sizex, sizey>  board,  b_board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    public:
    GOL(unsigned int seed) {
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            board.set(5,i+3, s[i]);
        }
    }
    
    void test() {
        std::cout << board.count_neighbours(5,4);
    }
    
    void step() {
        for (int i = 0; i < sizex; i++) {
            for (int j = 0; j < sizey; j++) {
                int neighbours = board.count_neighbours(i,j);
                b_board.set(i, j, board.get(i,j) * survive[neighbours] + (1 -  board.get(i,j)) * create[neighbours] );
            }
        }
        board.set(b_board.get());
    }
    
    void steps(int steps){
        for (int i = 0; i < steps; i++) {
            step();
        }
    }
    
    void print() {
        std::cout << "\u250f\u2501";
        for (int i = 0; i < sizey; i++) {
            std::cout << "\u2501\u2501";
        }
        std::cout << "\u2501\u2513\n";
        for (int i = 0; i < sizex; i++) {
            std::cout << "\u2503 ";
            for (int j = 0; j < sizey; j++) {
                if (board.get(i,j)) {
                    std::cout << "\u25A0 ";
                    //std::cout << board.count_neighbours(i, j) << " ";
                }
                else {
                    std::cout << "\u25A2 ";
                    //std::cout << board.count_neighbours(i, j) << " ";
                }
            }
            std::cout << " \u2503\n";
        }
        std::cout << "\u2517\u2501";
        for (int i = 0; i < sizey; i++) {
            std::cout << "\u2501\u2501";
        }
        std::cout << "\u2501\u251b\n";
    }
    
    bool* get_board() {
        return board;
    }
};
#endif
