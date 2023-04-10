#ifndef GOL_H
#define GOL_H

#include <bitset>
#include <thread>
#include <mutex>
#include <future>
#include "BitBoard.h"

class GOL {
    static const int No_Threads = 4;
    std::array<boost::dynamic_bitset<>, No_Threads> new_boards;
    std::array<std::thread, No_Threads> threads;
    protected:
    int sizex, sizey, len;
    BitBoard  board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    private:
    void m_step(const int index, int max, boost::dynamic_bitset<>& board);
    void o_step(boost::dynamic_bitset<>& board);
    
    public:
    GOL(int sx, int sy, unsigned int seed);
    
    GOL(unsigned int seed);
    
    GOL();
    
    void set_rules(const bool survive_[9], const bool create_[9]);
    
    void step();
    
    inline void steps(const int steps) { for (int i = 0; i < steps; ++i) { step(); } };
    
    void print();
    
    void set(const int index, const bool val);
    
    bool get(const int index);
    
    GOL& operator=(const GOL& other);
    
    BitBoard get_board();
};
#endif
