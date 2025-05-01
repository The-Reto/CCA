#include "BitBoard.h"
#include "BitBoardStreamBuf.h"
#include <fstream>

class BitBoardFileReader {
    public:
        explicit BitBoardFileReader(const std::string& filename);
    
        bool isOpen() const;
    
        bool run(BitBoardStreamBuf& sink);
    
    private:
        std::ifstream file;
        Bit_Board<u_int64_t> buffer;
};