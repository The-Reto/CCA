#ifndef GOL_RNG_H
#define GOL_RNG_H
#include "../headers/New_Implementation/Cryptographic_GOL_Board.h"
#include <bitset>

class GOL_RNG {
    
    Cryptographic_GOL_Board system;

    public:
    GOL_RNG(unsigned int seed_);
    
    int rand_int(unsigned int max = INT_MAX);
    
    long rand_long(unsigned int max = INT_MAX);
    
    bool rand_bit();
    
    float rand_float();
    
    double rand_double();
    
    void test();
    
};
#endif
