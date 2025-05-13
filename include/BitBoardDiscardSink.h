#include "BitBoard.h"
#include "BitBoardStreamBuf.h"

class BitBoardDiscardSink : public BitBoardStreamBuf {
    public:
        BitBoardDiscardSink() {}
        bool put(Bit_Board<u_int64_t> buffer, int size=BIT_BOARD_STREAM_BUFFER_SIZE) {return true;}
};

static BitBoardDiscardSink DISCARD_SINK = BitBoardDiscardSink();