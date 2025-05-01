#pragma once

#include "BitBoardStreamBuf.h"
#include <ostream>

class BitBoardOSink : public BitBoardStreamBuf {
public:
    BitBoardOSink(std::ostream& out);

    bool put(Bit_Board<u_int64_t> buffer, int size=BUFFER_SIZE) override;

private:
    std::ostream& out;
};