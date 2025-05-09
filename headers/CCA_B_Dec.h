#ifndef CCA_B_DEC_H
#define CCA_B_DEC_H

#include "CCA_B.h"

class CCA_B_Dec : public CCA_B
{
    Bit_Board<u_int64_t> key_buf;
    public:
    CCA_B_Dec(BitBoardStreamBuf& _next, std::string _key) : CCA_B(_next, _key) {}
    bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE);
};

#endif