#ifndef GOL_Enc_H
#define GOL_Enc_H

#include "CCA_Board.h"
#include "CCA_Key.h"
#include "BitBoardStreamBuf.h"

class CCA_S_Enc : public BitBoardStreamBuf
{
    private:

    CCA_Key key_manager;
    BitBoardStreamBuf& next;
            
    public:
    
    CCA_S_Enc(BitBoardStreamBuf& _next, std::string _key);
    
    bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE);
};
#endif
