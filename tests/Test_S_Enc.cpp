#include "../include/CCA_S_Enc.h"
#include "../include/BitBoardFileWriter.h"
#include "../include/BitBoardFileReader.h"
#include <boost/dynamic_bitset.hpp>
#include <fstream>

int main()
{
    BitBoardFileWriter out("./test_data/output/test.cts");
    CCA_S_Enc encryptor(out, "./test_data/test.trk");
    BitBoardFileReader file("./test_data/test.txt");
    file.run(encryptor);
    out.flush();

    BitBoardFileWriter out1("./test_data/output/test-dec.txt");
    CCA_S_Enc decryptor(out1, "./test_data/test.trk");
    BitBoardFileReader file1("./test_data/output/test.cts");
    file1.run(decryptor);
}
