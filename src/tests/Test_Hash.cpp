#include "../../headers/CCA_Hash.h"
#include "../../headers/BitBoardOSink.h"
#include "../../headers/BitBoardFileReader.h"

int main()
{
    BitBoardOSink out(std::cout);
    CCA_Hash hasher;
    BitBoardFileReader file("./test_data/test.txt");
    file.run(hasher);
    out.put(hasher.get_Hash());
}
