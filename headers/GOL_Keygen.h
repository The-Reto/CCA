#ifndef GOL_Key
#define GOL_Key
#include "C_GOL.h"
#include "BitBoard.h"

class GOL_Keygen {
    
    C_GOL gol_board;
    boost::dynamic_bitset<unsigned char> key;
    const static short SIZE_X = 128, SIZE_Y = 128, BLOCK_STEPS = 2;
    
    void setup();
    
    public:
    GOL_Keygen(boost::dynamic_bitset<unsigned char> key_);
    GOL_Keygen(std::string key_);
    
    boost::dynamic_bitset<unsigned char> get_streched_key(unsigned long len);
    
};
#endif
