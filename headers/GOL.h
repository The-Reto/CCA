#ifndef GOL_H
#define GOL_H

#include <bitset>
#include <thread>
#include <mutex>
#include "BitBoard.h"

class GOL {
    protected:
    int sizex, sizey,board_index;
    std::array<BitBoard,2>  boards;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    private:
    std::mutex m;
    void n_step(int index, int max);
    
    public:
    GOL(int sx, int sy, unsigned int seed);
    
    GOL(unsigned int seed);
    
    GOL();
    
    void set_rules(const bool survive_[9], const bool create_[9]);
    
    void step();
    
    void steps(int steps);
    
    void print();
    
    GOL& operator=(const GOL& other);
    
    BitBoard get_board();
};
#endif
