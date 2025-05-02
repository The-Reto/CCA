#ifndef BIT_BOARD_STREAM_BUFFER_H
#define BIT_BOARD_STREAM_BUFFER_H

#include "./BitBoard.h"

const static int BIT_BOARD_STREAM_BUFFER_SIZE = 64*64/8;

class BitBoardStreamBuf {
    public:
        virtual ~BitBoardStreamBuf() = default;
        virtual bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE) = 0;
    };

#endif