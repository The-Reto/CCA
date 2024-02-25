#ifndef GOL_Key
#define GOL_Key
#include "../headers/New_Implementation/Cryptographic_GOL_Board.h"
#include <bitset>

class GOL_Keygen {
    
    Cryptographic_GOL_Board gol_board;
    boost::dynamic_bitset<unsigned char> key, temp;
    const static short SIZE_X = 64, SIZE_Y = 64, BLOCK_STEPS = 2;
    
    void setup();
    
    public:
    GOL_Keygen(std::string key_);
    
    boost::dynamic_bitset<unsigned char> get_streched_key(unsigned long len);
    
};
#endif
