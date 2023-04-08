#ifndef GOL_CRYPTO_CPP
#define GOL_CRYPTO_CPP

#include "../headers/GOL_Crypto.h"

BitBoard GOL_CRYPTO::create_seed_map(unsigned int seed) {
    BitBoard map(sizex, sizey);
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    for (int i = sizex/5; i < sizex; ++i) { //adding noise
        for (int j = sizey/4; j < sizey/2; ++j) {
            map.set(j * sizex + i, s[(i*j+j) % (sizeof( int )*CHAR_BIT)]);
        }
    }
    return map;
}

GOL_CRYPTO::GOL_CRYPTO(int sx, int sy,unsigned int seed_) : GOL(sx,sy,seed_) {
	static bool survive_[9] = {0,0,0,1,0,1,0,0,0};
	static bool create_[9] =  {0,0,1,0,1,1,0,0,0};
    seed = seed_;

    seed_map = create_seed_map(seed);
    this->set_rules(survive_, create_);
    apply_xormap(seed_map);
    this->steps(std::max(sizex, sizey)); // distribute seed
}

GOL_CRYPTO::GOL_CRYPTO() : GOL_CRYPTO(1,1,0) {}

unsigned int GOL_CRYPTO::get_seed() {
    return seed;
}

void GOL_CRYPTO::apply_xormap(BitBoard map) {
    this->boards[board_index] = this->boards[board_index]^map;
}

#endif
