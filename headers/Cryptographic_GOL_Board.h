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

    /// @brief Does multiple steps in a loop
    /// @param steps (int) number of steps the system should take
    void steps(int steps);

    /// @brief updates the GOL-Board based on the LSB- and MSB-board
    void update_GOL_board();

    /// @brief spreads the seed over the board to initialize the random state
    void create_seed_map();

    /// @brief Applies a xor-map to the board
    /// @param xor_map u_int64_t array of length 64, will be xor-ed against the current state of the board
    void apply_xor_map(u_int64_t xor_map[size]);

    /// @brief returns the seed
    /// @return u_int64_t seed used to seed the board
    unsigned int get_seed();


    /// @brief Sets the seed, create_seed_map needs to be called after this for this to have any effect
    /// @param _seed u_int64_t seed used in create_seed_map
    void set_seed(u_int64_t _seed);

    /// @brief returns a random bitset of length len. Note: len should be much smaller than 4096 as that's the maximum number of bits on the board at any time.
    /// @tparam len (int) the length of the bitset to be returned 
    /// @return std::bitset<len> with pseudo random bits
    template<int len> std::bitset<len> rand_bits() {
        const static int multipliers[5] = {7,11,13,17,19};
        std::bitset<len> ret;
        const int multi = multipliers[seed%5];
        for (int i = 0; i < len; ++i) {
            ret[i] = get(multi*i+seed);
        }
        step();      
        return ret;
    }	
    
    /// @brief returns a random dynamic_bitset of length len. Note: len should be much smaller than 4096 as that's the maximum number of bits on the board at any time.
    /// @tparam len (int) the length of the bitset to be returned 
    /// @return boost::dynamic_bitset<unsigned char> with pseudo random bits
    template<int len> boost::dynamic_bitset<unsigned char> dynamic_rand_bits() {
        const static int multipliers[5] = {7,11,13,17,19};
        boost::dynamic_bitset<unsigned char> ret(len);
        const int multi = multipliers[seed%5];
        for (int i = 0; i < len; ++i) {
            ret[i] = get(multi*i+seed);
        }
        step();      
        return ret;
    }	

};
#endif