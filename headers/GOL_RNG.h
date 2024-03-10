#ifndef GOL_RNG_H
#define GOL_RNG_H
#include "Cryptographic_GOL_Board.h"
#include <bitset>

class GOL_RNG {
    
    Cryptographic_GOL_Board system;

    public:
    GOL_RNG(unsigned int seed_);
    
    int rand_int(unsigned int max = INT32_MAX);
    
    long rand_long(unsigned long max = INT64_MAX);
    
    bool rand_bit();
    
    float rand_float();
    
    double rand_double();
    
    void test();
    
};
#endif
