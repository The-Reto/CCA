#include "BitBoard.h"
#include "BitBoardOSink.h"
#include <fstream>

class BitBoardFileWriter : public BitBoardOSink {
    public:
        BitBoardFileWriter(std::string file_name) : fout(file_name, std::ios::binary), BitBoardOSink(fout) {}

    private:
        std::ofstream fout;
};