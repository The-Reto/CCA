#ifndef GOL_RNG_H
#define GOL_RNG_H
#include "CCA_Board.h"
#include <bitset>

class CCA_RNG {
    
    CCA_Board system;
    int int_ctr = 4096, long_ctr = 4096, float_ctr = 4096, double_ctr=4096, bit_ctr=4096;
    Bit_Board<u_int64_t> int_board, long_board, float_board, double_board, bit_board;

    public:
    CCA_RNG(unsigned int seed_);
    
    int rand_int(unsigned int max = INT32_MAX);
    
    long rand_long(unsigned long max = INT64_MAX);
    
    bool rand_bit();
    
    float rand_float();
    
    double rand_double();
    
    void test();
    
};
#endif
