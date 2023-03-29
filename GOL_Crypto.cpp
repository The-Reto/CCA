#ifndef GOL_CRYPTO_CPP
#define GOL_CRYPTO_CPP

#include "GOL.cpp"

template <int sizex, int sizey> class GOL_CRYPTO: public GOL< sizex, sizey> {
    protected:
    BitBoard< sizex, sizey> seed_map;
    unsigned int seed;
    
    BitBoard< sizex, sizey> create_seed_map(unsigned int seed) {
        BitBoard< sizex, sizey> map;
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = sizex/5; i < sizex; i++) { //adding noise
            for (int j = sizey/4; j < sizey/2; j++) {
                map.set(j * sizex + i, s[(i*j+j) % (sizeof( int )*CHAR_BIT)]);
            }
        }
        return map;
    }
    
    void step() {
    	GOL<sizex,sizey>::step();
    	seed_map = seed_map ^ this->board;
    	if (seed % 1024 == 0) {this->board = this->board ^ seed_map;}
    }

    public:
    GOL_CRYPTO(unsigned int seed_) : GOL<sizex,sizey>(seed_) {
    	static bool survive_[9] = {0,0,0,1,0,1,0,0,0};
    	static bool create_[9] =  {0,0,1,0,1,1,0,0,0};
        seed = (seed_ + 3141592) % INT_MAX;
 
        seed_map = create_seed_map(seed);
        this->set_rules(survive_, create_);
        apply_xormap(seed_map);
        this->steps(std::max(sizex, sizey)); // distribute seed
    }
    
    GOL_CRYPTO() : GOL<sizex,sizey>(0) {
	GOL_CRYPTO(0);
    }
    
    std::bitset<sizeof( int )*CHAR_BIT> rand_bits() {
    	const static int multipliers[5] = {3,5,7,11,13};
        std::bitset<sizeof( int )*CHAR_BIT> ret;
        int shift = seed % sizex*sizey;
        int multi = multipliers[seed%5];
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            ret[i] = this->board.get(multi*i+shift);
        }
        this->step();       
        seed = (seed+ret.to_ulong()) % INT_MAX;
        return ret;
    }
    
    unsigned int get_seed() {
        return seed;
    }
    
    void apply_xormap(BitBoard< sizex, sizey> map) {
	this->board = this->board^map;
    }
};
#endif
