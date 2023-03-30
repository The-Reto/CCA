#ifndef GOL_CRYPTO_CPP
#define GOL_CRYPTO_CPP

#include <exception>
#include "GOL.cpp"

class too_few_bits_exception: public std::exception {
    virtual const char* what() const throw() {
        return "Requested more random bits than the system can supply in one go";
    }
};

template <int sizex, int sizey> class GOL_CRYPTO: public GOL< sizex, sizey> {

    protected:
    BitBoard seed_map;
    unsigned int seed;
    
    BitBoard create_seed_map(unsigned int seed) {
        BitBoard map(sizex, sizey);
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = sizex/5; i < sizex; i++) { //adding noise
            for (int j = sizey/4; j < sizey/2; j++) {
                map.set(j * sizex + i, s[(i*j+j) % (sizeof( int )*CHAR_BIT)]);
            }
        }
        return map;
    }

    public:
    GOL_CRYPTO(unsigned int seed_) : GOL<sizex,sizey>(seed_) {
    	static bool survive_[9] = {0,0,0,1,0,1,0,0,0};
    	static bool create_[9] =  {0,0,1,0,1,1,0,0,0};
        seed = (seed_ + 3141592) % INT_MAX;
 
        seed_map = create_seed_map(seed);
        this->set_rules(survive_, create_);
        apply_xormap(seed_map);
        //this->steps(std::max(sizex, sizey)); // distribute seed
        std::cout << "yap" << std::endl;
    }
    
    GOL_CRYPTO() : GOL<sizex,sizey>(0) {
	GOL_CRYPTO(0);
    }
    
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
    
    unsigned int get_seed() {
        return seed;
    }
    
    void apply_xormap(BitBoard map) {
	this->board = this->board^map;
    }
    
    void step() {
    	GOL<sizex,sizey>::step();
    	seed_map = seed_map ^ this->board;
    	if (seed % 1024 == 0) {this->board = this->board ^ seed_map;}
    }
};
#endif
