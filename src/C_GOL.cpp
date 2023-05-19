#ifndef GOL_CRYPTO_CPP
#define GOL_CRYPTO_CPP

#include "../headers/C_GOL.h"

BitBoard C_GOL::create_seed_map(unsigned int seed) {
    const static int multipliers[5] = {5,127,2293,1427,503}; //Prime Number No. 3,31,314,225,96
    BitBoard map(sizex, sizey);
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    for (int i : multipliers) {
        for (int j = 0; j < sizex*sizey; ++j) {
            map.set(j*i, s[j]^map.get(j));
        }
    }
    return map;
}

C_GOL::C_GOL(int sx, int sy,unsigned int seed_) : GOL(sx,sy,0) {
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
