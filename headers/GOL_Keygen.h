#ifndef GOL_Key
#define GOL_Key
#include "Cryptographic_GOL_Board.h"
#include <bitset>

class GOL_Keygen {
    
    Cryptographic_GOL_Board gol_board;
    Bit_Board<u_int64_t> key, temp;
    const static short SIZE_X = 64, SIZE_Y = 64, BLOCK_STEPS = 2;
    
    void setup();
    
    public:
    GOL_Keygen(std::string key_);
    
    Bit_Board<u_int64_t>  get_streched_key();
    
};
#endif
