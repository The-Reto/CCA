#include "./GOL_Board.h"
#include <boost/dynamic_bitset.hpp>

#ifndef TOOFEWBITS
#define TOOFEWBITS

class too_few_bits_exception: public std::exception {
    virtual const char* what() const throw() {
        return "Requested more random bits than the system can supply in one go";
    }
};

#endif

#ifndef CRYPTOGRAPHIC_GOL_BOARD
#define CRYPTOGRAPHIC_GOL_BOARD

/// @brief A GOL-Board with flexible, customizable, rules - slower than a class where the rules are hardcoded
/// @tparam TYPE u_intX_t used to store the bord, simultaneously sets width of GOL-Board (eg. u_int32_t, sets the width to 32)
/// @tparam size height of the GOL-Board
class Cryptographic_GOL_Board: public GOL_Board<u_int64_t, 64> {
    const static int size = 64;

    u_int64_t seed;
    public:
    /// @brief Default constructor, set the rules to "vanilla" Conway GOL 
    Cryptographic_GOL_Board(unsigned int _seed);
    Cryptographic_GOL_Board();

    /// @brief Does one GOL-Update step
    void step(); 

    void steps(int steps);

    /// @brief updates the GOL-Board based on the LSB- and MSB-board
    void update_GOL_board();

    void create_seed_map();

    void apply_xor_map(u_int64_t xor_map[size]);

    unsigned int get_seed();
    void set_seed(u_int64_t _seed);

    template<int len> std::bitset<len> rand_bits() {
        if (len > size) {throw too_few_bits_exception();}
        const static int multipliers[5] = {7,11,13,17,19};
        std::bitset<len> ret, to_seed(64);
        const int shift = seed % size*size;
        const int multi = multipliers[seed%5];
        for (int i = 0; i < len; ++i) {
            ret[i] = get(multi*i+shift);
        }
        for (int i = len; i < len + 64; ++i) {
            to_seed[i-len] = get(multi*i+shift);
        }
        seed ^= ( seed + to_seed.to_ulong() ) % INT_MAX;
        step();      
        return ret;
    }	
    
    template<int len> boost::dynamic_bitset<unsigned char> dynamic_rand_bits() {
        if (len > size * size / 2) {throw too_few_bits_exception();}
        const static int multipliers[5] = {7,11,13,17,19};
        boost::dynamic_bitset<unsigned char> ret(len), to_seed(64);
        const int shift = seed % size*size;
        const int multi = multipliers[seed%5];
        for (int i = 0; i < len; ++i) {
            ret[i] = get(multi*i+shift);
        }
        for (int i = len; i < len + 64; ++i) {
            to_seed[i-len] = get(multi*i+shift);
        }
        seed ^= ( seed + to_seed.to_ulong() ) % INT_MAX;
        step();      
        return ret;
    }	

};
#endif