#include "../../headers/CCA_B.h"

void CCA_B::update_F(Bit_Board<u_int64_t> &buffer, short ofset, short cycle)
{
    const static short multi[32] = {2,3,5,6,7,9,10,11,12,13,14,15,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,33,34,35,36,37};
    for (short i = 0; i < 32; i++) { 
        F[0][i] = buffer[i + ofset] ^ (*key)[i * multi[cycle]];
    }
    for (short i = 32; i < 64; i++) {
        F[0][i] = CCA_Board::pi[i];
    }
    F.steps(4);
}

void CCA_B::update_Key(Bit_Board<u_int64_t> &buffer)
{
    key = key_manager.get_streched_key();
    for (short i = 0; i < 64; i++) { 
        (*key)[i] ^= buffer[i];
    }
}

CCA_B::CCA_B(BitBoardStreamBuf &_next, std::string _key) : next(_next), key_manager(_key)
{
    key = key_manager.get_streched_key();
}

