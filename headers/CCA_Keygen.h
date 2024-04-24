#ifndef GOL_Key
#define GOL_Key
#include "CCA_Board.h"
#include <bitset>

class CCA_Keygen {
    
    CCA_Board gol_board;
    Bit_Board<u_int64_t> key, temp;
    const static short SIZE_X = 64, SIZE_Y = 64, BLOCK_STEPS = 2;
    
    void setup();
    
    public:
    CCA_Keygen(std::string key_);
    
    Bit_Board<u_int64_t>  get_streched_key();
    
};
#endif
