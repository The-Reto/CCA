#ifndef GOL_Key
#define GOL_Key
#include "CCA_Board.h"
#include <bitset>

class CCA_Key : public CCA_Board {
    
    const static short SIZE_X = 64, SIZE_Y = 64;
    
    public:
    CCA_Key(Bit_Board<u_int64_t> _key);
    
    Bit_Board<u_int64_t>* get_streched_key();
    Bit_Board<u_int64_t>* get_key();

    static CCA_Key generate_key(std::string user_input);
    
};
#endif
