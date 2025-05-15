#ifndef CCA_B_ENC_H
#define CCA_B_ENC_H

#include "CCA_B.h"

class CCA_B_Enc : public CCA_B
{
    public:
    CCA_B_Enc(BitBoardStreamBuf& _next, std::string _key, Bit_Board<u_int64_t> _iv);
    bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE);
};

#endif