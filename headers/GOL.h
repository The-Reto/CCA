#ifndef GOL_H
#define GOL_H

#include <bitset>
#include <thread>
#include <mutex>
#include <future>
#include "BitBoard.h"

class GOL {
    static const int No_Threads = 6;
    std::array<boost::dynamic_bitset<unsigned char>, No_Threads+1> new_boards;
    std::array<std::thread, No_Threads> threads;
    protected:
    int sizex, sizey, len;
    BitBoard  board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0}, create[9] =  {0,0,0,1,0,0,0,0,0}, multi_thread = false;
    
    private:
    void m_step(const int index, const int max, boost::dynamic_bitset<unsigned char>& board);
    
    public:
    GOL(int sx, int sy, unsigned int seed);
    
    inline GOL(unsigned int seed) : GOL(1,1,seed) {}
    
    inline GOL() : GOL(1,1,0) {}
    
    void set_rules(const bool survive_[9], const bool create_[9]);
    
    void step();
    
    inline void steps(const int steps) {for (int i = 0; i < steps; ++i) { step(); }};
    
    inline void print() {board.visualize();}
    
    inline void set(const int index, const bool val) {board.set(index, val);}
    
    inline bool get(const int index) {return board.get(index);}
    
    GOL& operator=(const GOL& other);
    
    inline BitBoard get_board() {return board;}
};
#endif
