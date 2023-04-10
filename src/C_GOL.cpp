#ifndef GOL_CRYPTO_CPP
#define GOL_CRYPTO_CPP

#include "../headers/C_GOL.h"

BitBoard C_GOL::create_seed_map(unsigned int seed) {
    BitBoard map(sizex, sizey);
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    for (int i = sizex/5; i < sizex; ++i) { //adding noise
        for (int j = sizey/4; j < sizey/2; ++j) {
            map.set(j * sizex + i, s[(i*j+j) % (sizeof( int )*CHAR_BIT)]);
        }
    }
    return map;
}

C_GOL::C_GOL(int sx, int sy,unsigned int seed_) : GOL(sx,sy,seed_) {
	static bool survive_[9] = {0,0,0,1,0,1,0,0,0};
	static bool create_[9] =  {0,0,1,0,1,1,0,0,0};
    seed = seed_;

    seed_map = create_seed_map(seed);
    set_rules(survive_, create_);
    apply_xormap(seed_map);
    steps(std::max(sizex, sizey)); // distribute seed
}

C_GOL::C_GOL() : C_GOL(1,1,0) {}

unsigned int C_GOL::get_seed() {
    return seed;
}

void C_GOL::apply_xormap(BitBoard &map) {
    board = board^map;
}

#endif
