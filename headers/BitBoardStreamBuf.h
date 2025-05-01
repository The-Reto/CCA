#ifndef BIT_BOARD_STREAM_BUFFER_H
#define BIT_BOARD_STREAM_BUFFER_H

#include "./BitBoard.h"

class BitBoardStreamBuf {
    public:
        const static int BUFFER_SIZE = 64*64/8;

        virtual ~BitBoardStreamBuf() = default;
        virtual bool put(Bit_Board<u_int64_t> buffer, int size=BUFFER_SIZE) = 0;
    };

#endif