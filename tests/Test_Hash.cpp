#include "../include/CCA_Hash.h"
#include "../include/BitBoardOSink.h"
#include "../include/BitBoardFileReader.h"

int main()
{
    BitBoardOSink out(std::cout);
    CCA_Hash hasher;
    BitBoardFileReader file("./test_data/test.txt");
    file.run(hasher);
    out.put(hasher.get_Hash());
}
