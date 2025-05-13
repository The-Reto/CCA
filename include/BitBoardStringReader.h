#include "BitBoard.h"
#include "BitBoardStreamBuf.h"
#include <sstream>

class BitBoardStringReader {
    public:
        explicit BitBoardStringReader(const std::string& string);
     
        bool run(BitBoardStreamBuf& sink);
    
    private:
        std::istringstream str_stream;
        Bit_Board<u_int64_t> buffer;
};