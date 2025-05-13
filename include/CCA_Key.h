#ifndef GOL_Key
#define GOL_Key
#include "CCA_Board.h"

class CCA_Key : public CCA_Board {
    
    const static short SIZE_X = 64, SIZE_Y = 64;
    
    public:
    CCA_Key(Bit_Board<u_int64_t> _key);
    
    Bit_Board<u_int64_t>* get_streched_key();
    Bit_Board<u_int64_t>* get_key();

    static bool write_key_to_file(CCA_Key key, std::string path);

    static CCA_Key generate_key(std::string user_input);

    static CCA_Key read_key(std::string path);
    
};
#endif
