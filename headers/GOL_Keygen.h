#ifndef GOL_Key
#define GOL_Key
#include "C_GOL.h"
#include "BitBoard.h"

class GOL_Keygen {
    
    C_GOL gol_board, salt;
    boost::dynamic_bitset<unsigned char> key;
    bool salted;
    const static short SIZE_X = 64, SIZE_Y = 64, HASH_SIZE = SIZE_X * SIZE_Y / CHAR_BIT, BLOCK_STEPS = 1;
    
    void setup();
    
    public:
    GOL_Keygen(boost::dynamic_bitset<unsigned char> key_);
    GOL_Keygen(std::string key_);
    
    boost::dynamic_bitset<unsigned char> get_streched_key(unsigned long len);
    
    void set_salt();
    BitBoard get_salt();
    
};
#endif
