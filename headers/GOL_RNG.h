#ifndef GOL_RNG_H
#define GOL_RNG_H
#include "GOL_Crypto.h"

class GOL_RNG {
    
    GOL_CRYPTO system;

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
