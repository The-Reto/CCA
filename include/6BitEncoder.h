#ifndef SIXBIT_ENCODER_H
#define SIXBIT_ENCODER_H

#include "BitBoardOSink.h"

class SixBitEncoder : public BitBoardOSink
{
    private:

    constexpr static char symbols[65] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ<>";
            
    public:
    
    SixBitEncoder(std::ostream& _out);
    
    bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE);
};
#endif