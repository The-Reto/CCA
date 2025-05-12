#pragma once

#include "BitBoardStreamBuf.h"
#include <ostream>

class BitBoardOSink : public BitBoardStreamBuf {
public:
    BitBoardOSink(std::ostream& out);

    bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE) override;

    void flush();

protected:
    std::ostream& out;
};