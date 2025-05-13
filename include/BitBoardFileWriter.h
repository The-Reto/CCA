#include "BitBoard.h"
#include "BitBoardOSink.h"
#include <fstream>

class BitBoardFileWriter : public BitBoardOSink {
    public:
        BitBoardFileWriter(std::string file_name) : out(file_name, std::ios::binary), BitBoardOSink(out) {}

        void flush() {out.flush();}

    private:
        std::ofstream out;
};