#ifndef GOL_CRYPTO_CPP
#define GOL_CRYPTO_CPP

#include "GOL.cpp"

template <int sizex, int sizey> class GOL_CRYPTO: public GOL< sizex, sizey> {
    protected:
    BitBoard< sizex, sizey> seed;
    
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
    
    void set_rules(bool choice) {
        const static bool survive_[18] = {0,0,1,1,0,1,0,0,0, 0,0,1,0,1,1,1,0,1};
        const static bool create_[18] =  {0,0,1,0,1,1,0,0,0, 0,0,1,0,1,0,1,0,1};
        for (int i = 0 + choice*9; i < 9 + choice*9; i++) {
            this->survive[i - choice*9] = survive_[i];
            this->create[i - choice*9] = create_[i];
        }
    }

    public:
    GOL_CRYPTO(unsigned int seed_) : GOL<sizex,sizey>(seed_) {
        seed_ = (seed_ + 3141592) % INT_MAX;
 
        seed = create_seed_map(seed_);
        set_rules(seed.get(23,65));
        apply_xormap(seed, sizex, sizey);
        this->steps(std::max(sizex, sizey)); // distribute seed
    }
    
    GOL_CRYPTO() : GOL<sizex,sizey>(0) {

    }
    
    std::bitset<sizeof( int )*CHAR_BIT> rand_bits() {
        std::bitset<sizeof( int )*CHAR_BIT> ret;
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            ret[i] = this->board.get(i, sizex/3);
        }
        this->step();
        seed.set(seed.get() ^ this->board.get());
        set_rules(ret[0]);
        return std::bitset<sizeof( int )*CHAR_BIT>(ret);
    }
    
    unsigned int get_seed() {
        return seed;
    }
    
    void apply_xormap(BitBoard< sizex, sizey> map, int x, int y) {
        for (int i = 0; i < x; i++) { //adding noise
            for (int j = 0; j < y; j++) {
                this->board.set(i,j, this->board.get(i,j)^map.get(j * x + i));
            }
        }
    }
};
#endif
