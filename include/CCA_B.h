#ifndef CCA_B_H
#define CCA_B_H

#include "CCA_Board.h"
#include "CCA_Keygen.h"
#include "BitBoardStreamBuf.h"

class CCA_B : public BitBoardStreamBuf
{
    protected:
    CCA_Keygen key_manager;
    BitBoardStreamBuf& next;
    CCA_Board F;
    Bit_Board<u_int64_t> *key, prev;

    void update_F(Bit_Board<u_int64_t>& buffer, short ofset, short cycle);
    void update_Key(Bit_Board<u_int64_t>& buffer);
            
    public:
    
    static const short ROUNDS = 16;

    CCA_B(BitBoardStreamBuf& _next, std::string _key);
    
    virtual bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE) = 0;
};

#endif
