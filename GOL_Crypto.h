#ifndef GOL_CRYPTO_H
#define GOL_CRYPTO_H

#include <exception>
#include "GOL.h"

class too_few_bits_exception: public std::exception {
    virtual const char* what() const throw() {
        return "Requested more random bits than the system can supply in one go";
    }
};

class GOL_CRYPTO: public GOL {

    protected:
    BitBoard seed_map;
    unsigned int seed;
    
    BitBoard create_seed_map(unsigned int seed);

    public:
    GOL_CRYPTO(int sx, int sy,unsigned int seed_);
    
    GOL_CRYPTO();
    
    unsigned int get_seed();
    
    void apply_xormap(BitBoard map);
    
    void step();
    
    template<int len> std::bitset<len> rand_bits() {
        if (len > std::max(sizex, sizey)) {throw too_few_bits_exception();}
        const static int multipliers[5] = {3,5,7,11,13};
        std::bitset<len> ret;
        int shift = seed % sizex*sizey;
        int multi = multipliers[seed%5];
        for (int i = 0; i < len; i++) {
            ret[i] = this->board.get(multi*i+shift);
        }
        this->step();       
        seed = ( seed + *reinterpret_cast<unsigned int *>(&ret) ) % INT_MAX;
        return ret;
    }	
};
#endif
