#ifndef GOL_HASH_H
#define GOL_HASH_H
#include "CCA_Board.h"
#include "BitBoardStreamBuf.h"
#include "BitBoard.h"

class CCA_Hash : public BitBoardStreamBuf {    
    public:
    const static short SIZE_X = 64, SIZE_Y = 64, HASH_SIZE = SIZE_X * SIZE_Y / CHAR_BIT, BLOCK_STEPS = 1, MIX_STEPS = 64;    

    CCA_Hash(BitBoardStreamBuf& _next);
    CCA_Hash();
    
    bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE);

    Bit_Board<u_int64_t> get_Hash();

    private:
    CCA_Board gol_board;    
    BitBoardStreamBuf& next;
    bool hash_calculated;

    void add_to_hash(Bit_Board<u_int64_t>& _buffer);
    
};
#endif
